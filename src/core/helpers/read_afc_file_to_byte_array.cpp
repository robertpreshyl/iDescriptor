#include "../../iDescriptor.h"
#include <QByteArray>
#include <QDebug>

QByteArray read_afc_file_to_byte_array(afc_client_t afcClient, const char *path)
{
    uint64_t fd_handle = 0;
    afc_error_t fd_err =
        afc_file_open(afcClient, path, AFC_FOPEN_RDONLY, &fd_handle);

    if (fd_err != AFC_E_SUCCESS) {
        qDebug() << "Could not open file" << path;
        return QByteArray();
    }

    // TODO: is this necessary
    char **info = NULL;
    afc_get_file_info(afcClient, path, &info);
    uint64_t fileSize = 0;
    if (info) {
        for (int i = 0; info[i]; i += 2) {
            if (strcmp(info[i], "st_size") == 0) {
                fileSize = std::stoull(info[i + 1]);
                break;
            }
        }
        afc_dictionary_free(info);
    }

    if (fileSize == 0) {
        afc_file_close(afcClient, fd_handle);
        return QByteArray();
    }

    QByteArray buffer;

    buffer.resize(fileSize);
    uint32_t bytesRead = 0;
    afc_file_read(afcClient, fd_handle, buffer.data(), buffer.size(),
                  &bytesRead);

    if (bytesRead != fileSize) {
        qDebug() << "AFC Error: Read mismatch for file" << path;
        return QByteArray(); // Read failed
    }

    return buffer;
};
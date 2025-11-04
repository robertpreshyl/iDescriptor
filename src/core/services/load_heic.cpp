/*
 * iDescriptor: A free and open-source idevice management tool.
 *
 * Copyright (C) 2025 Uncore <https://github.com/uncor3>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "../../iDescriptor.h"
#include <QByteArray>
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <libheif/heif.h>

QPixmap load_heic(const QByteArray &imageData)
{
    heif_context *ctx = heif_context_alloc();
    if (!ctx) {
        qWarning() << "Failed to allocate heif_context";
        return QPixmap();
    }

    heif_error err = heif_context_read_from_memory(ctx, imageData.constData(),
                                                   imageData.size(), nullptr);
    if (err.code != heif_error_Ok) {
        qWarning() << "Failed to read HEIC from memory:" << err.message;
        heif_context_free(ctx);
        return QPixmap();
    }

    heif_image_handle *handle;
    err = heif_context_get_primary_image_handle(ctx, &handle);
    if (err.code != heif_error_Ok) {
        qWarning() << "Failed to get primary image handle:" << err.message;
        heif_context_free(ctx);
        return QPixmap();
    }

    heif_image *img;
    err = heif_decode_image(handle, &img, heif_colorspace_RGB,
                            heif_chroma_interleaved_RGB, nullptr);
    if (err.code != heif_error_Ok) {
        qWarning() << "Failed to decode HEIC image:" << err.message;
        heif_image_handle_release(handle);
        heif_context_free(ctx);
        return QPixmap();
    }

    int width = heif_image_get_width(img, heif_channel_interleaved);
    int height = heif_image_get_height(img, heif_channel_interleaved);
    int stride;
    /*
     FIXME: use heif_image_get_plane_readonly2 in future, on ubuntu 24 it's not
     available yet
    */
    const uint8_t *data =
        heif_image_get_plane_readonly(img, heif_channel_interleaved, &stride);

    if (!data) {
        qWarning() << "Failed to get image plane data";
        heif_image_release(img);
        heif_image_handle_release(handle);
        heif_context_free(ctx);
        return QPixmap();
    }

    QImage qimg(data, width, height, stride, QImage::Format_RGB888);
    QPixmap result = QPixmap::fromImage(qimg);

    heif_image_release(img);
    heif_image_handle_release(handle);
    heif_context_free(ctx);

    return result;
}

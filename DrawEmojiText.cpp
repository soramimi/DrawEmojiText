#include "DrawEmojiText.h"

#include <QIcon>

void drawEmojiText(QPainter *painter, int x, int y, QString const &text)
{
	QFontMetrics fm = painter->fontMetrics();
	int ascent = fm.ascent();
	int emoji_w = ascent;
	int emoji_h = ascent;

	ushort const *begin = text.utf16();
	ushort const *end = begin + text.size();
	ushort const *head = begin;
	ushort const *tail = begin;

	auto DrawText = [&](QString const &text){
		painter->drawText(x, y, text);
		x += fm.size(0, text).width();
	};

	auto Flush = [&](){
		if (head < tail) {
			DrawText(QString::fromUtf16(head, tail - head));
			head = tail;
		}
	};

	auto Gray = [](QRgb rgb){
		return (qRed(rgb) * 306 + qGreen(rgb) * 601 + qBlue(rgb) * 117) / 1024;
	};

	QColor color = painter->pen().color();

	while (tail < end) {
		if (*tail == '&') {
			if (tail + 1 < end && tail[1] == '&') {
				tail++;
				Flush();
				head++;
				tail = head;
			} else {
				Flush();
				head++;
				for (tail = head; tail < end; tail++) {
					if (*tail == ';') {
						QString symbol = QString::fromUtf16(head, tail - head);
						if (symbol == "amp") {
							DrawText("&");
						} else if (symbol.startsWith(':')) {
							bool mono = false;
							bool invert = false;
							while (1) {
								int i = symbol.lastIndexOf('|');
								if (i < 0) break;
								if (symbol.mid(i + 1) == "mono") {
									mono = true;
								} else if (symbol.mid(i + 1) == "invert") {
									invert = true;
								}
								symbol = symbol.mid(0, i);
							}
							QIcon icon(symbol);
							if (!icon.isNull()) {
								QImage img(emoji_w, emoji_h, QImage::Format_ARGB32);
								img.fill(Qt::transparent);
								{
									int alpha = painter->pen().color().alpha();
									QPainter p(&img);
									p.setOpacity(alpha / 255.0);
									icon.paint(&p, QRect(0, 0, emoji_w, emoji_h));
								}
								if (mono) {
									for (int y = 0; y < emoji_h; y++) {
										QRgb *p = reinterpret_cast<QRgb *>(img.scanLine(y));
										for (int x = 0; x < emoji_w; x++) {
											int v = Gray(p[x]);
											if (invert) v = 255 - v;
											int a = qAlpha(p[x]);
											p[x] = qRgba(color.red(), color.green(), color.blue(), v * a / 255);
										}
									}
								}
								painter->drawImage(x, y - ascent, img, 0, 0, emoji_w, emoji_h);
								x += emoji_w;
							}
						}
						tail++;
						break;
					}
				}
				head = tail;
				tail = head;
			}
			continue;
		}
		tail++;
	}
	Flush();
}

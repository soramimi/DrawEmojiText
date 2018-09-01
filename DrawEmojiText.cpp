#include "DrawEmojiText.h"

#include <QIcon>

void DrawEmojiText(QPainter *painter, int x, int y, QString const &text)
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
							QIcon icon(symbol);
							if (!icon.isNull()) {
								icon.paint(painter, QRect(x, y - ascent, emoji_w, emoji_h));
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

#include "MyCentralWidget.h"
#include "DrawEmojiText.h"
#include <QDebug>
#include <QIcon>
#include <QPainter>

MyCentralWidget::MyCentralWidget(QWidget *parent)
    : QWidget(parent)
{
}

void MyCentralWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setFont(QFont("Times New Roman", 30));

	QFontMetrics fm = painter.fontMetrics();
	int lineheight = fm.height();;
	int x = 0;
	int y = 0;

	QString text = "&:/image/cuctus.svg;Hello&:/image/sushi.svg;world&:/image/thinking.svg;&:/image/sushi.svg|mono|invert;";


	y += lineheight;
	painter.setPen(QColor(255, 0, 0, 255));
	drawEmojiText(&painter, x, y, text);

	y += lineheight;
	painter.setPen(QColor(128, 192, 160, 192));
	drawEmojiText(&painter, x, y, text);

	y += lineheight;
	painter.setPen(QColor(0, 80, 255, 96));
	drawEmojiText(&painter, x, y, text);
}

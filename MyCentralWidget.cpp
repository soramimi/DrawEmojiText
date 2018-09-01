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
	painter.setPen(Qt::black);

	QFontMetrics fm = painter.fontMetrics();
	int x = 0;
	int y = fm.height();

	QString text = "&:/image/cuctus.svg;Hello&:/image/sushi.svg;world&:/image/thinking.svg;";
	DrawEmojiText(&painter, x, y, text);
}

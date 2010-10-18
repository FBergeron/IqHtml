/*  IQNotes - Smarty notes
    Copyright (C) 2001 Peter Vrabel <kybu@kybu.sk>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; version 2 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/

#include "qsketch.h"

#include <QPainter>
#include <QBrush>
#include <QColor>
#include <QMenu>
#include <QColorDialog>


Stroke::Stroke()
{
    init(0, QColor().black());
}

Stroke::Stroke(uint width, QColor color)
{
    init(width, color);
}

void Stroke::init(uint width, QColor color)
{
    pen.setWidth(width);
    pen.setColor(color);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setCapStyle(Qt::RoundCap);

    // The setAutoDelete() method is not available anymore in the API so comment the following line out. - FB
    //points.setAutoDelete(true);
}

void Stroke::addPoint(const QPoint point)
{
    QPoint *p = new QPoint(point);
    points << (*p);
}

void Stroke::paint(QPainter *p, bool onlyLastPoint)
{
    const QPen &oldPen = p->pen();
    p->setPen(pen);

    if (points.count() == 1 && !onlyLastPoint)
    {
        QPoint *point = &(points.first());

        p->drawEllipse(point->x() - int(pen.width()/2), point->y() - int(pen.width()/2), pen.width(), pen.width());
    }
    // paint all points
    else if (!onlyLastPoint)
    {
        QPainterPath path;
        for( QList<QPoint>::iterator it = points.begin(); it != points.end(); ++it )
        {
            QPoint point = *it;
            // It's first point
            if (point == points.first())
                path.moveTo( point );

            path.lineTo( point );
        }
        p->drawPath( path );
    }
    // paint only last point
    else
    {
        if( points.size() >= 2 ) {
            QPoint last = points.at( points.size() - 1 );
            QPoint prev = points.at( points.size() - 2 );
            p->drawLine( prev, last );
        }
    }

    p->setPen(oldPen);
}

QString Stroke::serialize()
{
    QString r;
    r.sprintf("%d,%d,%d,%d", pen.width(), pen.color().red(), pen.color().green(), pen.color().blue());

    for( QList<QPoint>::iterator it = points.begin(); it != points.end(); ++it ) 
    {
        QPoint point = *it;
        QString p;
        r += p.sprintf(",%d,%d", point.x(), point.y());
    }

    return r;
}

void Stroke::unserialize(QString data)
{
    QString p;
    uint idx = 0, red, green, blue;
    QPoint point;
    QColor color;

    points.clear();

    for (int i = 0; i < data.length(); i++)
    {
        if (!(data[i] == ','))
        {
            p += data[i];
        }
        else
        {
            // width
            if (idx == 0)
            {
                pen.setWidth(p.toInt());
                p = "";
                idx++;
            }
            // red
            else if (idx == 1)
            {
                red = p.toInt();
                p = "";
                idx++;
            }
            // green
            else if (idx == 2)
            {
                green = p.toInt();
                p = "";
                idx++;
            }
            // blue
            else if (idx == 3)
            {
                blue = p.toInt();
                p = "";
                idx++;
            }
            // X
            else if ((idx % 2) == 0)
            {
                point.setX(p.toInt());
                p = "";
                idx++;
            }
            // Y
            else
            {
                point.setY(p.toInt());
                p = "";
                idx++;

                addPoint(point);
            }
        }
    }

    point.setY(p.toInt());
    addPoint(point);

    color.setRgb(red, green, blue);
    pen.setColor(color);
}





Strokes::Strokes()
{
    currentStroke = 0;
    // The setAutoDelete() method is not available anymore in the API so comment the following line out. - FB
    //strokes.setAutoDelete(true);
}

Strokes::Strokes(Strokes &strks)
{
    strokes.clear();
    for (QList<Stroke*>::ConstIterator it = strks.constBegin(); it != strks.constEnd(); it++ ) {
        Stroke* stroke = *it;
        QString d = stroke->serialize();
        qDebug() << qPrintable( d ) << endl;
        addStroke(stroke->serialize());
    }
}

Strokes::~Strokes()
{
    closeStroke();
}

void Strokes::openStroke(uint width, QColor color)
{
    currentStroke = new Stroke(width, color);
}

void Strokes::addPoint(const QPoint point)
{
    if (!currentStroke)
        return;

    currentStroke->addPoint(point);
}

void Strokes::closeStroke()
{
    //if (currentStroke)
    //    strokes << *currentStroke;

    currentStroke = 0;
}

void Strokes::paint(QPainter *p)
{
    for (QList<Stroke*>::iterator it = strokes.begin(); it != strokes.end(); ++it ) 
    {
        Stroke* stroke = *it;
        stroke->paint(p);
    }

    if (currentStroke)
        currentStroke->paint(p);
}

void Strokes::removeLastStroke()
{
    strokes.removeLast();
}

QString Strokes::serialize()
{
    QString r;
    uint i = 0;

    for( QList<Stroke*>::iterator it = strokes.begin(); it != strokes.end(); ++it ) 
    {
        Stroke* stroke = *it;
        QString p;

        r += p.sprintf("stroke%d=\"", i) + stroke->serialize() + "\"\n";
    }

    return r;
}

void Strokes::addStroke(const QString &serialData)
{
    Stroke *stroke = new Stroke();

    stroke->unserialize(serialData);
    strokes << stroke;
}


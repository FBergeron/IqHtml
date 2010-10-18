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
#ifndef QSKETCH_H
#define QSKETCH_H

#include <QPixmap>
#include <QWidget>
#include <QList>
#include <QPen>
#include <QDebug>

class Stroke
{
public:
    Stroke();
    Stroke(Stroke &s)
    {
        unserialize(s.serialize());
    }
    Stroke(uint width, QColor color);
    void addPoint(const QPoint point);

    void paint(QPainter *p, bool onlyLastPoint = false);

    QString serialize() ;
    void unserialize(QString data);

    uint getWidth()
    {
        return pen.width();
    }
    QColor getColor()
    {
        return pen.color();
    }

private:
    void init(uint width, QColor color);

    QList<QPoint> points;
    QPen pen;
};


class Strokes
{
public:
    Strokes();
    Strokes(Strokes &strks);
    ~Strokes();

    // open new stroke
    void openStroke(uint width, QColor color);
    // add point to current stroke
    void addPoint(const QPoint point);
    // close current stroke
    void closeStroke();
    //
    void removeLastStroke();

    QString serialize();
    void addStroke(const QString &serialData);

    // opened stroke
    Stroke *getCurrentStroke()
    {
        return currentStroke;
    }
    // closed stroke
    Stroke *getLastStroke()
    {
        return( strokes.last() );
    }

    QList<Stroke*>::ConstIterator constBegin() const {
        return( strokes.constBegin() );
    }

    QList<Stroke*>::ConstIterator constEnd() const {
        return( strokes.constEnd() );
    }

    void paint(QPainter *p);

private:
    QList<Stroke*> strokes;
    Stroke *currentStroke;
};


#endif

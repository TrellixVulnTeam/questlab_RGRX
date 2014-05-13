
#ifndef __QL_QSTCOMMINT_H__
#define __QL_QSTCOMMINT_H__

#include "QstComm.h"

#pragma warning (push)
#pragma warning (disable: 4127)
#pragma warning (disable: 4512)
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#pragma warning (pop)

/************************/
/* 实现自动滚动的文本框 */
/************************/
class CTextEdit : public QTextEdit
{
    Q_OBJECT

public:
    CTextEdit (QWidget* parent = 0) : QTextEdit(parent)
    {
    }

public slots:
    void autoScroll ()
    {
        QTextCursor cursor = this->textCursor();

        cursor.movePosition(QTextCursor::End);

        this->setTextCursor(cursor);
    }
};

/**************************************************/
/* 为了解决多线程问题的信号类 (需要人肉 moc 处理) */
/**************************************************/
class CTextOper : public QObject
{
    Q_OBJECT

public:
    CTextOper (QMainWindow* form, QTextEdit* edit)
    {
        connect(this, SIGNAL(quit()), form, SLOT(close()));
        connect(this, SIGNAL(gotoEnd()), edit, SLOT(autoScroll()));
        connect(this, SIGNAL(allClear()), edit, SLOT(clear()));
        connect(this, SIGNAL(allSelect()), edit, SLOT(selectAll()));
        connect(this, SIGNAL(setText(const QString&)),
                edit, SLOT(insertPlainText(const QString&)));
        connect(this, SIGNAL(setHtml(const QString&)),
                edit, SLOT(insertHtml(const QString&)));
        connect(this, SIGNAL(setFont(const QFont&)),
                edit, SLOT(setCurrentFont(const QFont&)));
        connect(this, SIGNAL(setStyle(const QString&)),
                edit, SLOT(setStyleSheet(const QString&)));
    }

public:
    void exit ()
    {
        emit quit();
    }
    void clear ()
    {
        emit allClear();
    }
    void text (const QString& text)
    {
        emit gotoEnd();
        emit setText(text);
    }
    void html (const QString& html)
    {
        emit gotoEnd();
        emit setHtml(html);
    }
    void setup (const QFont& font, const QString& style)
    {
        emit allSelect();
        emit setFont(font);
        emit setStyle(style);
        emit gotoEnd();
    }

signals:
    void quit ();
    void gotoEnd ();
    void allClear ();
    void allSelect ();
    void setText (const QString& text);
    void setHtml (const QString& html);
    void setFont (const QFont& font);
    void setStyle (const QString& style);
};

#endif  /* !__QL_QSTCOMMINT_H__ */

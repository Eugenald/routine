#include <iostream>
#include <QDebug>
#include "CMazeDebugger.h"

CMazeDebugger::CMazeDebugger(QTextEdit* textWidget)
   :mTextWidget(textWidget)
{

}

void CMazeDebugger::setText(const QString& text)
{
   mTextWidget->setText(text);
}

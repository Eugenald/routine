#pragma once

#include <QWidget>
#include <QTextEdit>
#include <widgets/MazeLabel.h>

class CMazeDebugger
{
public:
   explicit CMazeDebugger(QTextEdit* textWidget);
   ~CMazeDebugger() = default;
   CMazeDebugger(const CMazeDebugger&) = delete;
   CMazeDebugger& operator= (const CMazeDebugger&) = delete;

   void setText(const QString& text);

private:
   QTextEdit* mTextWidget;
};

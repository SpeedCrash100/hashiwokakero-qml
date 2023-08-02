#pragma once

#include <memory.h>
#include <qqml.h>

#include <QObject>

#include "hashiwokakero.hpp"

class BoardLogic : public QObject {
  Q_OBJECT
  QML_ELEMENT

  Q_PROPERTY(int columnsCount READ columnsCount WRITE setColumnsCount NOTIFY
                 columnCountChanged FINAL)
  Q_PROPERTY(int rowsCount READ rowsCount WRITE setRowsCount NOTIFY
                 rowsCountChanged FINAL)
  Q_PROPERTY(int stepCount READ stepCount WRITE setStepCount NOTIFY
                 stepCountChanged FINAL)

  Q_PROPERTY(QVariant islands READ islands NOTIFY islandsChanged FINAL)
  Q_PROPERTY(QVariant bridges READ bridges NOTIFY bridgesChanged FINAL)
  Q_PROPERTY(bool solved READ solved NOTIFY solvedChanged FINAL)

 public:
  explicit BoardLogic(QObject* parent = nullptr);

  int columnsCount() const;
  void setColumnsCount(int columns);

  int rowsCount() const;
  void setRowsCount(int rows);

  int stepCount() const;
  void setStepCount(int steps);

  QVariant islands() const;
  QVariant bridges() const;
  bool solved() const;

  Q_INVOKABLE void generateBoard();

  Q_INVOKABLE bool buildBridge(int row1, int column1, int row2, int column2);

 signals:
  void columnCountChanged(int columns);
  void rowsCountChanged(int rows);
  void stepCountChanged(int steps);
  void islandsChanged(QVariant islands);
  void bridgesChanged(QVariant bridges);
  void solvedChanged(bool solved);

 private:
  int m_nCols;
  int m_nRows;
  int m_steps;

  std::shared_ptr<Board> m_board;
  bool m_solved;
};

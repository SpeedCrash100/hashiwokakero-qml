#include "boardlogic.hpp"

#include <QMap>
#include <algorithm>
#include <format>

BoardLogic::BoardLogic(QObject* parent) : m_nCols(7), m_nRows(7), m_steps(7) {
  generateBoard();
}

int BoardLogic::columnsCount() const { return m_nCols; }

void BoardLogic::setColumnsCount(int columns) {
  if (m_nCols != columns) {
    m_nCols = columns;
    emit columnCountChanged(columns);
    generateBoard();
  }
}

int BoardLogic::rowsCount() const { return m_nRows; }

void BoardLogic::setRowsCount(int rows) {
  if (m_nRows != rows) {
    m_nRows = rows;
    emit rowsCountChanged(rows);
    generateBoard();
  }
}

int BoardLogic::stepCount() const { return m_steps; }

void BoardLogic::setStepCount(int steps) {
  if (m_steps != steps) {
    m_steps = steps;
    emit stepCountChanged(steps);
    generateBoard();
  }
}

QVariant BoardLogic::islands() const {
  auto islands = m_board->islands();
  auto transformed_islands = QVariantList();
  transformed_islands.resize(islands.size());

  std::transform(islands.begin(), islands.end(), transformed_islands.begin(),
                 [](const Island& island) {
                   QMap<QString, QVariant> obj{
                       {"r", island.position.x},
                       {"c", island.position.y},
                       {"req", island.bridgeRequired},
                   };

                   return obj;
                 });

  return transformed_islands;
}

void BoardLogic::generateBoard() {
  BoardBuilder builder;
  builder.setHeight(m_nRows);
  builder.setWidth(m_nCols);
  m_board = builder.build(m_steps);

  emit islandsChanged(islands());
}

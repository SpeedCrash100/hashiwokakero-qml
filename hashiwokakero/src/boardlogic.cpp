#include "boardlogic.hpp"

#include <QMap>
#include <algorithm>
#include <format>
#include <iostream>

BoardLogic::BoardLogic(QObject* parent)
    : m_nCols(7), m_nRows(7), m_steps(7), m_solved(false), QObject(parent) {
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
                       {"r", island.position.row},
                       {"c", island.position.col},
                       {"req", island.bridgeRequired},
                       {"rem", island.bridgesRemaining},
                   };

                   return obj;
                 });

  return transformed_islands;
}

QVariant BoardLogic::bridges() const {
  auto bridges = m_board->bridges();
  auto transformed_bridges = QVariantList();
  transformed_bridges.resize(bridges.size());

  std::transform(bridges.begin(), bridges.end(), transformed_bridges.begin(),
                 [](const Bridge& bridge) {
                   QMap<QString, QVariant> pos1{
                       {"r", bridge.first.row},
                       {"c", bridge.first.col},
                   };

                   QMap<QString, QVariant> pos2{
                       {"r", bridge.second.row},
                       {"c", bridge.second.col},
                   };

                   QMap<QString, QVariant> obj{{"first", pos1},
                                               {"second", pos2},
                                               {"size", bridge.size}};

                   return obj;
                 });

  return transformed_bridges;
}

bool BoardLogic::solved() const { return m_solved; }

void BoardLogic::generateBoard() {
  BoardBuilder builder;
  builder.setHeight(m_nRows);
  builder.setWidth(m_nCols);

  int steps = m_steps;

  while (true) {
    try {
      m_board = builder.build(steps);
      break;
    } catch (const std::runtime_error&) {
      steps--;
    }
  }

  emit islandsChanged(islands());
}

Q_INVOKABLE bool BoardLogic::buildBridge(int row1, int column1, int row2,
                                         int column2) {
  auto res = m_board->tryBuildBridge(Island(BoardPosition(row1, column1)),
                                     Island(BoardPosition(row2, column2)));

  if (res) {
    auto new_solved = m_board->solved();
    if (m_solved != new_solved) {
      m_solved = new_solved;
      emit solvedChanged(m_solved);
    }
    emit islandsChanged(islands());
    emit bridgesChanged(bridges());
    return true;
  }
  return false;
}

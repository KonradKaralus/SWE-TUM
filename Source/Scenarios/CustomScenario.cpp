/**
 * @file
 * This file is part of SWE.
 *
 * @author Michael Bader, Kaveh Rahnema, Tobias Schnabel
 * @author Sebastian Rettenberger (rettenbs AT in.tum.de,
 * http://www5.in.tum.de/wiki/index.php/Sebastian_Rettenberger,_M.Sc.)
 *
 * @section LICENSE
 *
 * SWE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SWE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SWE.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * @section DESCRIPTION
 *
 * TODO
 */

#include "CustomScenario.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>


RealType Scenarios::CustomScenario::getWaterHeight(RealType x, RealType y) const {
  return RealType((sqrt((x - 200.0) * (x - 200.0) + (y - 200.0) * (y - 200.0)) < 100.0) ? 20.0 : 10.0);
}

RealType Scenarios::CustomScenario::getBathymetry([[maybe_unused]] RealType x, [[maybe_unused]] RealType y) const {}

double Scenarios::CustomScenario::getEndSimulationTime() const { return double(15); }

BoundaryType Scenarios::CustomScenario::getBoundaryType([[maybe_unused]] BoundaryEdge edge) const { return BoundaryType::Wall; }

RealType Scenarios::CustomScenario::getBoundaryPos(BoundaryEdge edge) const {
  if (edge == BoundaryEdge::Left) {
    return RealType(0.0);
  } else if (edge == BoundaryEdge::Right) {
    return RealType(1000.0);
  } else if (edge == BoundaryEdge::Bottom) {
    return RealType(0.0);
  } else {
    return RealType(500.0);
  }
}


void Scenarios::CustomScenario::setPath(std::string path) {
  this->path = path;

  std::ifstream file("filename.ext");

  int i = 0;

  for (std::string line; getline(file, line);) {
    if (i == 0) {
      this->width = std::stoi(line);
    } else if (i == 1) {
      this->height = std::stoi(line);
    } else if (i == 2) {
      std::stringstream ss(line);
      std::string       item;

      int offset = 0;

      while (getline(ss, item, ',')) {
        this->content[offset] = std::stoi(item);
        offset++;
      }
    }
    i++;
  }
}

RealType Scenarios::CustomScenario::getBathymetry([[maybe_unused]] RealType x, [[maybe_unused]] RealType y) const {
  if (x <= 1 || y <= 1) {
    return 0;
  }
  x = floor(x - 1);
  y = floor(y - 1);

  auto idx  = (int(round(x)) + this->width * (500 - int(round(y))));
  auto byte = this->content[int(floor(idx))];

  return (float(byte) / 255.0) * 10.0;
}

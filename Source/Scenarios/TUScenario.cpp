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

#include "TUScenario.hpp"

#include <cmath>

#include <iostream>

RealType Scenarios::TUScenario::getWaterHeight(RealType x, RealType y) const {
  return RealType((sqrt((x - 500.0) * (x - 500.0) + (y - 250.0) * (y - 250.0)) < 100.0) ? 15.0 : 10.0);
}

RealType Scenarios::TUScenario::getBathymetry([[maybe_unused]] RealType x, [[maybe_unused]] RealType y) const {
  auto idx = (int(round(x)) + x_len * int(round(y)));

  // std::cout << "Tried to get x,y:" << x << y << std::endl;

  auto byte = epd_bitmap_szenTU[int(floor(idx / 8))] & int(pow(2, idx % 8));

  if (byte != 0) {
    return 100.0;
  } else {
    return 0.0;
  }
}

double Scenarios::TUScenario::getEndSimulationTime() const { return double(15); }

BoundaryType Scenarios::TUScenario::getBoundaryType([[maybe_unused]] BoundaryEdge edge) const { return BoundaryType::Outflow; }

RealType Scenarios::TUScenario::getBoundaryPos(BoundaryEdge edge) const {
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

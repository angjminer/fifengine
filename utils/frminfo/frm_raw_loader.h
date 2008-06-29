/***************************************************************************
 *   Copyright (C) 2005-2006 by the FIFE Team                              *
 *   fife-public@lists.sourceforge.net                                     *
 *   This file is part of FIFE.                                            *
 *                                                                         *
 *   FIFE is free software; you can redistribute it and/or modify          *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA              *
 ***************************************************************************/

#ifndef FIFE_RAW_LOADER_H
#define FIFE_RAW_LOADER_H

// Standard C++ library includes

// 3rd party library includes

// FIFE includes

namespace FIFE {
  class map::loaders::fallout::AnimatedPalette;
	class RawFRM : public map::loaders::fallout::FRM {
		public:
			RawFRM(const std::string & fname, map::loaders::fallout::AnimatedPalette* palette);
			uint8_t* getFrameRaw(uint16_t dir, uint16_t frame);
			uint8_t* getFrameRGBA(uint16_t dir, uint16_t frame);
			std::pair<uint16_t, uint16_t> getFrameDimension(uint16_t dir, uint16_t frame);
	};
}
#endif

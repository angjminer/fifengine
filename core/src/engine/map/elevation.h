/***************************************************************************
 *   Copyright (C) 2005-2007 by the FIFE Team                              *
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

#ifndef FIFE_MAP_ELEVATION_H
#define FIFE_MAP_ELEVATION_H

// Standard C++ library includes
#include <list>
#include <vector>

// 3rd party library includes

// FIFE includes
// These includes are split up in two parts, separated by one empty line
// First block: files included from the FIFE root src directory
// Second block: files included from the same folder
#include "attributedclass.h"

#include "structure.h"

namespace FIFE { namespace map {

	class ObjectGrid;
	class Grid;
	class Object;

	/** Contains a game level.
	 * 
	 * Or more exactly: stores (a number of) other objects that contain
	 * the actual data:
	 * \li @see MapTile
	 * \li @see Object
	 *
	 * Tiles are only graphics and they are on a separate grid.
	 *
	 * Objects can be: critters, items, walls, scenery and non-visible 
	 * entities (blockers).
	 *
	 * \todo Objects are stored in a std::list; this causes a number of
	 * problems:
	 *
	 * \note Search the wiki for: fallout map geometry; the hex-grid should
	 * work with a left->right, back->front drawing order.
	 *
	 * \todo One hex-grid may be occupied by more than one object; we need
	 * to handle this case, probably with some made-up logic.
	 * (for example: objects get an (artificial) size; ~smallest~ object 
	 * drawn first, larger ones above)
	 *
	 * \todo This seems like the right place to add pathfinding/line-of-sight.
	 *
	 * \todo Export the yet unwritten functionality into the scriptengine...
	 * ... and we are a lot closer to a game.
	 *
	 */
	class Elevation : public AttributedClass {
		public:

			Elevation(const elevation_info& structure);
			~Elevation();

			/** Add a grid at the top
			 * The elevation now owns the grid.
			 * Increases num grids by one.
			 */
			void addGrid(Grid* grid);
			void setGrid(size_t numgrids, Grid* grid);
			Grid* getGrid(size_t);
			size_t getNumGrids() const;
			void setNumGrids(size_t numgrids);

			/** Set the 'reference' grid
			 */
			void setReferenceGrid(size_t grid);

			/** Get the 'reference' grid
			 */
			map::Grid* getReferenceGrid();

			/** Try to calculate a valid nice starting position
			 */
			Point centerOfMass();

		private:
			typedef std::vector<map::Grid*> type_grids;
			type_grids m_grids;

			int m_width;
			int m_height;
			size_t m_reference_grid;

			void cleanup();

			// Not copyable.
			Elevation(const Elevation&);
			Elevation& operator=(const Elevation&);
	};

} } //FIFE::map

#endif
/* vim: set noexpandtab: set shiftwidth=2: set tabstop=2: */
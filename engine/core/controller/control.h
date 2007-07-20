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

#ifndef FIFE_MAP_CONTROL_H
#define FIFE_MAP_CONTROL_H

// Standard C++ library includes
#include <string>
#include <set>

// 3rd party library includes
#include <boost/shared_ptr.hpp>

// FIFE includes
// These includes are split up in two parts, separated by one empty line
// First block: files included from the FIFE root src directory
// Second block: files included from the same folder
#include "util/point.h"

namespace FIFE { 
	class SettingsManager;

	class Screen;

namespace map {

	class Map;
	typedef boost::shared_ptr<Map> MapPtr;

	class MapLoader;

	class ObjectInfo;

	class Camera;
	class View;

	/** The controlling class binding together dynamic environment and visualisation
	 *  This class must be instantiated to have a visible, life map. It will
	 *  take care of setting up the environment for rendering and scripting.
	 *
	 *  @bug The states probably do NOT work correctly. (WORK IN PROGRESS)
	 */
	class Control {
		public:
			/** Constructor
			 */
			Control();

			/** Destructor
			 */
			~Control();

			/** add a map loader to Control
			 *
			 * @note an appropriate map loader must be provided to Control
			 * before load or save calls can be made.
			 */
			void addMapLoader(MapLoader* loader);
	
			/** Load and set a map from a map file
			 *  Does the equivalent to
			 *  @code
			 *  map_control.setMap( Map::load(filename) )
			 *  @endcode
			 */
			void load(const std::string& filename);

			/** Save the map to a map file
			 */
			void save(const std::string& filename);

			/** Sets a map to be controlled
			 *  If a map is already in use, this will call @b stop()
			 *  but not @b start().
			 */
			void setMap(MapPtr map);

			/** Start a map - setting up script environment and rendering.
			 */
			void start();

			/** Update the map view
			 */
			void update();

			/** Stop a map - shuting down script environment and rendering.
			 */
			void stop();

			/** Return the 'started' state of the map
			 */
			bool isRunning() const;

			/** Switch to another elevation
			 */
			void setElevation(size_t);
			
			/** Get current elevation
			 */
			size_t getCurrentElevation() const;

			/** Get the number of elevations on the map
			 */
			size_t getNumElevations() const;

			/** Make a selection; returns the geometry coordinate of the selection
			 */
			Point select(const Point& mousept, size_t layer);

			/** Create a script-controlled dynamic object on the specified
			 * layer of the current elevation.
			 */
			ObjectInfo* createDynamicObject(size_t layer, Point p, char* prototype);

			/** Return the map view used by this control
			 */
			View* getView();

			/** Returns the screen (render target) used by this control
			 */
			Screen* getScreen();

			/** Return the map operated by this control
			 */
			MapPtr getMap();

			/** Clear the currently loaded map
			 */
			void clearMap();

			Camera* createCamera();
			void deleteCamera(Camera* camera);

		protected:

			void activateElevation(size_t elevation_id);

			std::string m_map_filename;
			MapPtr m_map;
			Screen* m_screen;
			View* m_view;
			SettingsManager* m_settings;
			std::set<Camera*> m_cameras;

			typedef std::map<std::string, MapLoader*> type_loaders;
			type_loaders m_loaders;

			bool m_isrunning;
			size_t m_elevation;

			void resetCameras();
	};

} } // FIFE::map

#endif // FIFE_MAPCONTROL_H

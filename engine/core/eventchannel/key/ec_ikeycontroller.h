/***************************************************************************
 *   Copyright (C) 2005-2008 by the FIFE team                              *
 *   http://www.fifengine.de                                               *
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

#ifndef FIFE_EVENTCHANNEL_IKEY_CONTROLLER_H
#define FIFE_EVENTCHANNEL_IKEY_CONTROLLER_H

// Standard C++ library includes
//

// 3rd party library includes
//

// FIFE includes
// These includes are split up in two parts, separated by one empty line
// First block: files included from the FIFE root src directory
// Second block: files included from the same folder
//

namespace FIFE {
	class IKeyListener;

	/**  Controller provides a way to receive events from the system
	 * Using this interface, clients can subscribe themselves to receive events
	 */
	class IKeyController {
	public:

		/** Adds a listener to the controller
		 * Listener will be notified via the corresponding events
		 * @param listener listener to add
		 */
		virtual void addKeyListener(IKeyListener* listener) = 0;

		/** Removes an added listener from the controller.
		 * Listener will not be notified anymore via the corresponding events
		 * @param listener listener to remove
		 */
		virtual void removeKeyListener(IKeyListener* listener) = 0;

		virtual ~IKeyController() {}
	};

} //FIFE

#endif

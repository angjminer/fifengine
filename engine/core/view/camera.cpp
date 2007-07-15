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

// Standard C++ library includes

// 3rd party library includes
#include <boost/bind.hpp>

// Platform specific includes
#include "util/fife_math.h"

// FIFE includes
// These includes are split up in two parts, separated by one empty line
// First block: files included from the FIFE root src directory
// Second block: files included from the same folder
#include "util/time/timemanager.h"
#include "video/screen.h"
#include "model/geometries/geometry.h"
#include "model/structures/elevation.h"
#include "model/structures/layer.h"
#include "model/structures/objectinfo.h"

#include "camera.h"
#include "view.h"
#include "visual.h"

namespace FIFE { namespace map {

	Camera::Camera(View* view) {
		m_view = view;
		m_timer.setInterval(50);
		m_timer.setCallback( boost::bind( &Camera::update, this ) );

		int w = m_view->getScreen()->getWidth();
		int h = m_view->getScreen()->getHeight();

		setViewport(Rect(0, 0, w, h));

		reset();
	}

	Camera::~Camera() {
		m_timer.stop();
		m_tracked_object.reset();
		m_layer.reset();
	}

	void Camera::update() {
		switch(m_mode) {
			case TRACKING:
			{
				if( m_tracked_object ) {
					m_tracked_visual = m_tracked_object->getVisualId();
				}
				if( !m_view || !m_view->isValidVisualId(m_tracked_visual) )
					return;
		
				Visual* visual = m_view->getVisual(m_tracked_visual);
		
				Rect screen_box = visual->getScreenBox();
				m_next_position = Point(screen_box.x + screen_box.w/2,
				                        screen_box.y + screen_box.h/2);
			}
			// FALL THROUGH

			case MOVING:
			{
				Point dist = m_next_position - m_position;
				
				uint32_t length = dist.length();
				if (length < 50) {
					m_timer.stop();
					return;
				}
				
				Debug("map_camera") 
					<< "Zooming from " << m_position
					<< " to " << m_next_position
					<< " by " << (dist*50) / length;
				
				m_position += (dist*50) / length;
			}
			break;
	
			case FREE:
			break;
	
		}
	}

	void Camera::track( size_t visualId ) {
		m_tracked_object.reset();
		m_tracked_visual = visualId;
		m_timer.start();
		m_mode = TRACKING;
	}

	void Camera::track( ObjectPtr object ) {
		m_tracked_object = object;
		m_timer.start();
		m_mode = TRACKING;
	}

	void Camera::moveBy(const Point& delta) {
		m_tracked_object.reset();
		m_position += delta;
		m_timer.stop();
		m_mode = FREE;
	}

	void Camera::jumpTo(const Point& position) {
		m_tracked_object.reset();
		if( !m_layer )
			return;

		Point offset = Point(m_viewport.w, m_viewport.h) / 2;
		m_position = m_layer->getGeometry()->toScreen(position) - offset;

		m_timer.stop();
		m_mode = FREE;
	}

	void Camera::moveTo(const Point& position) {
		m_tracked_object.reset();
		if (!m_layer) {
			return;
		}
		// center on screen
		Point offset = Point(m_viewport.w, m_viewport.h) / 2;
		m_next_position = m_layer->getGeometry()->toScreen(position) - offset;
		m_timer.start();

		Debug("map_camera") 
			<< "Setting Next position:" << m_next_position;
		m_mode = MOVING;
	}

	void Camera::render() {
		m_view->setXPos(m_position.x);
		m_view->setYPos(m_position.y);
		m_view->setViewport(m_viewport);
		m_view->render();
	}

	void Camera::reset() {
		m_tracked_object.reset();
		m_layer.reset();

		m_timer.stop();
		if (!m_view->getCurrentElevation()) {
			m_position = Point();
			m_mode = FREE;
		} else {
			m_layer = m_view->getCurrentElevation()->getReferenceLayer();
			m_position = Point(m_view->getXPos(),m_view->getYPos());
			m_mode = FREE;
		}
	}

	void Camera::setViewport(const Rect& viewport) {
		m_viewport = viewport;
	}

} } // FIFE::map

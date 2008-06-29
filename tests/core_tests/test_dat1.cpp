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

// Standard C++ library includes
#include <iostream>
#include <iomanip>

// Platform specific includes

// 3rd party library includes

// FIFE includes
// These includes are split up in two parts, separated by one empty line
// First block: files included from the FIFE root src directory
// Second block: files included from the same folder
#include "vfs/vfs.h"
#include "vfs/vfsdirectory.h"
#include "vfs/dat/dat1.h"
#include "vfs/raw/rawdata.h"
#include "util/base/exception.h"

#include "fife_unit_test.h"

using boost::unit_test::test_suite;
using namespace FIFE;

static const std::string COMPRESSED_FILE = "../data/dat1vfstest.dat";
static const std::string RAW_FILE = "../data/test.map";

#ifdef FIFE_BOOST_VERSION_103300
void test_decoder() {
#else
BOOST_AUTO_TEST_CASE( DAT1_test ) {
#endif
	boost::shared_ptr<VFS> vfs(new VFS());
	vfs->addSource(new VFSDirectory(vfs.get()));

	if ((!vfs->exists(COMPRESSED_FILE))) {
		BOOST_ERROR("Test source " << COMPRESSED_FILE << " not found");
		return;
	}

	vfs->addSource(new DAT1(vfs.get(), COMPRESSED_FILE));

	if ((!vfs->exists(RAW_FILE)) || (!vfs->exists("dat1vfstest.map"))) {
		BOOST_ERROR("Test files not found");
	}

	RawData* fraw = vfs->open(RAW_FILE);
	RawData* fcomp = vfs->open("dat1vfstest.map");

	if (fraw->getDataLength() != fcomp->getDataLength()) {
		std::cout << "raw length = " << fraw->getDataLength() \
				  << ", compressed length = " << fcomp->getDataLength() << std::endl;
		BOOST_ERROR("Data length mismatch");
	} else {
		std::cout << "data length match, length = " << fcomp->getDataLength() << std::endl;
	}

	unsigned int smaller_len = fraw->getDataLength();
	if (fcomp->getDataLength() < smaller_len) {
		smaller_len = fcomp->getDataLength();
	}

	uint8_t* d_raw  = new uint8_t[fraw->getDataLength()];
	uint8_t* d_comp = new uint8_t[fcomp->getDataLength()];
	fraw->readInto(d_raw,fraw->getDataLength());
	fcomp->readInto(d_comp,fcomp->getDataLength());

	std::cout << "scanning data..." << std::endl;
	for (unsigned int i = 0; i < smaller_len; i++) {
		uint8_t rawc =  d_raw[i];
		uint8_t compc = d_comp[i];
		if (rawc != compc) {
			BOOST_ERROR("Data mismatch");
			std::cout 
				<< "raw: " << std::setbase(16) << rawc 
				<< " comp: " << std::setbase(16) << compc << std::endl;
			break;
		}
	}
	std::cout << "scanning finished" << std::endl;
	delete[] d_raw;
	delete[] d_comp;
	delete fraw;
	delete fcomp;
}

#ifdef FIFE_BOOST_VERSION_103300
test_suite* init_unit_test_suite(int argc, char** const argv) {
	test_suite* test = BOOST_TEST_SUITE("DAT1 tests");
	test->add(BOOST_TEST_CASE(&test_decoder), 0);
	return test;
}
#endif

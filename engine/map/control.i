%module mapcontrol
%{
#include "map/control.h"
%}

namespace FIFE { namespace map {

  class MapLoader;

	class Control {
		public:
			Control();
			~Control();

			void leaseMapLoader(MapLoader* loader);

			void load(const std::string& filename);
      
			void start();
			void stop();
			bool isRunning();

			size_t getCurrentElevation();
			void setElevation(size_t);

		private:
	};
}}

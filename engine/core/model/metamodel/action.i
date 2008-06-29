%module fife
%{
#include "model/metamodel/action.h"
%}

%include "util/base/utilbase.i"
%include "model/metamodel/abstractvisual.i"

namespace FIFE {

	class Action : public ResourceClass {
	public:
		Action(const std::string& identifier);
		virtual ~Action();
		const std::string& getId();
		void adoptVisual(AbstractVisual* visual);
		template<typename T> T* getVisual() const;
		void setDuration(unsigned int duration);
		unsigned int getDuration();
	};
}

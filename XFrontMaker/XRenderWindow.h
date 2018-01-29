#pragma once

#include "XGLWindow.h"

namespace Smile
{
	class XRenderWindow : public XGLWindow
	{
		void Begin();
		void Render();
		void End();
	};
}
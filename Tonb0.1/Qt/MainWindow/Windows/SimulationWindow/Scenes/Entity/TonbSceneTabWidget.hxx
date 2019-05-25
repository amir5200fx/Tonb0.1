#pragma once
#ifndef _TonbSceneTabWidget_Header
#define _TonbSceneTabWidget_Header

#include <QtWidgets/qtabwidget.h>

namespace AutLib
{

	class SimulationWindow;
	class TonbTWI;

	class TonbSceneTabWidget
		: public QTabWidget
	{

	public:

		TonbSceneTabWidget(SimulationWindow* parentwindow = 0, TonbTWI* parent = 0, const QString& title = "");
	};
}

#endif // !_TonbSceneTabWidget_Header

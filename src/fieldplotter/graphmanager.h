#pragma once

#include <graphics/renderer.h>
#include <components/chargesystem.h>
#include <components/fieldlines.h>

#include <memory>

/*
The user-facing aggregate of various graphical components, along with some methods for moving them around.

A user needs to be able to:
	- add or remove charges (doing so warrants a recomputing of field lines)
	- reconfigure the field lines
	- resize charges (recomputing optional)
	- move the camera
*/

enum Graphical_Components {
	CHARGE_SYSTEM=0,
	FIELD_LINES
};

class GraphManager {
	public:
		void addCharge(PointCharge const& charge);
		void modifyCharge(int index, PointCharge const& charge);
		void removeCharge(int index);
		void configureFieldLines(FieldLines::Configuration const& new_configuration);
		void scrollCamera(float amount);
		void orbitCamera(int);
		void setVisible(Graphical_Components component, bool visible);
		void initializeGL();
	private:
		bool m_glInit;
		std::unique_ptr<Renderer> m_renderer;
		std::unique_ptr<FieldLines> m_fieldlines;
		std::unique_ptr<ChargeSystem> m_chargesystem;
};
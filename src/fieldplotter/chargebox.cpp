#include "chargebox.h"

//(0,0,0.5);0.1

using namespace std;

const regex ChargeValidator::form = regex("(sub)(.*)");

QValidator::State ChargeValidator::validate(QString& input, int& pos) const {

	return State::Acceptable;
}
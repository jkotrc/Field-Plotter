#pragma once

#include <QtWidgets/QLineEdit>
#include <QValidator>

#include <regex>;

//(0,0,0.5);0.1

class ChargeValidator : public QValidator {
private:
	QDoubleValidator number_validator;
	static const std::regex form;
public:
	QValidator::State validate(QString& input, int& pos) const override;
	
};

class ChargeBox : public QLineEdit {
	
};
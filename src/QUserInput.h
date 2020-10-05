/*
	Copyright 2015-2019 Rafael Dellà Bort. silderan (at) gmail (dot) com

	This file is part of QMikPPPManager

	QMikPPPManager is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as
	published by the Free Software Foundation, either version 3 of
	the License, or (at your option) any later version.

	QMikPPPManager is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	and GNU Lesser General Public License. along with QMikPPPManager.
	If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef UTILS_QUSERINPUT_H
#define UTILS_QUSERINPUT_H

#include <QInputDialog>
#include <QMessageBox>
#include <QRegExp>

namespace Utils {

bool userInputLine(QString &out, QWidget *parent, const QString &title, const QString &text, const QRegExp &forbiddenChars, bool allowEmpty = false)
{
	QString rtn;
	if( !allowEmpty )
	{
repeat:
		rtn = QInputDialog::getText(parent, title, text, QLineEdit::Normal);
		if( rtn.isEmpty() )
		{
			QMessageBox::warning(parent, title, QObject::tr("Cancelado") );
			return false;
		}
		if( rtn.contains(forbiddenChars) )
		{
			QMessageBox::warning(parent, title, QObject::tr("El texto contiene caracteres no válidos") );
			goto repeat;
		}
		out = rtn;
		return true;
	}
	else
	{
		rtn = QInputDialog::getText(parent, title, text, QLineEdit::Normal);
		if( rtn.isEmpty() )
		{
			out.clear();
			return true;
		}
		if( rtn.contains(forbiddenChars) )
			QMessageBox::warning(parent, title, QObject::tr("El texto contiene caracteres no válidos. Cancelado") );
	}
	return false;
}

bool userInputLine(QString &out, QWidget *parent, const QString &title, const QString &text, const QString &forbiddenChars, bool allowEmpty = false)
{
	return userInputLine(out, parent, title, text, QRegExp(forbiddenChars), allowEmpty);
}

}
#endif // UTILS_QUSERINPUT_H

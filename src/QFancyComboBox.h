#ifndef QFANCYCOMBOBOX_H
#define QFANCYCOMBOBOX_H

#include <QComboBox>

class QFancyComboBox : public QComboBox
{
	bool m_hasDefaultData;

public:
	explicit QFancyComboBox(QWidget *papi = Q_NULLPTR)
	    : QComboBox(papi)
	    , m_hasDefaultData(false)
	{	}

	virtual void setup(const QString &defaultValueDescription, const QString &defaultValueData, const QStringList &addList, const QStringList &skipList, const QString &currentSelected)
	{
		clear();

		if( (m_hasDefaultData = !defaultValueDescription.isEmpty()) )
			addItem( defaultValueDescription, defaultValueData );

		int i = -1;
		foreach( QString t, addList )
		{
			if( t == currentSelected )
			{
				i = count();
				addItem(t);
			}
			else
				if( !skipList.contains(t) )
					addItem(t);
		}
		if( count() )
		{
			if( i == -1 )
			{
				if( !defaultValueDescription.isEmpty() )
					i = 0;
				else
					if( !currentSelected.isEmpty() )
					{
						i = count();
						addItem(currentSelected);
					}
			}
			setCurrentIndex(i);
		}
	}
	virtual void setup(const QStringList &addList, const QString &currentSelected, bool addIfNecessary = false)
	{
		clear();
		if( currentSelected.isEmpty() )
			return setup(addList);
		addItems(addList);
		return selectText(currentSelected, addIfNecessary);
	}
	virtual void updateList(const QStringList &addList, bool addIfNecessary = false)
	{
		if( currentText().isEmpty() )
			return setup(addList);
		else
			return setup(addList, currentText(), addIfNecessary );
	}
	virtual void setup(const QStringList &addList) { addItems(addList);	}
	QString currentText()
	{
		if( (currentIndex() == 0) && m_hasDefaultData )
			return currentData().toString();
		return QComboBox::currentText();
	}
	void selectText(const QString &text, bool addIfNecessary = false)
	{
		int i = findData(text, Qt::EditRole);
		if( i == -1 )
		{
			if( addIfNecessary )
			{
				i = count();
				addItem(text);
			}
			else
				return setCurrentText(text);
		}
		setCurrentIndex(i);
	}
};

#endif // QFANCYCOMBOBOX_H

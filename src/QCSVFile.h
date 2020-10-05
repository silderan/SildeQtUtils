#ifndef QCSVFILE_H
#define QCSVFILE_H

#include <QString>
#include <QFile>
#include <functional>

#include <QList>

class QCSVFile
{
public:
	static bool loadFile(const QString &file, std::function<void(const QStringList &txt)>fnc )
	{
		QFile f(file);
		if( f.open(QIODevice::ReadOnly) )
		{
			QByteArray linea;
			QList<QByteArray> bits;
			QStringList out;
			while( !f.atEnd() )
				if( (linea = f.readLine().replace("\n", "")).count() )
				{
					bits = linea.split('\t');
					if( out.count() != bits.count() )
						out.reserve(bits.count());
					for( QByteArray txt : bits )
						out.append( QString::fromLatin1(txt.replace("\\t", "\t")) );

					fnc(out);
				}
			f.close();
			return true;
		}
		return false;
	}
//	static bool saveFile(const QString &file, )
};

#endif // QCSVFILE_H

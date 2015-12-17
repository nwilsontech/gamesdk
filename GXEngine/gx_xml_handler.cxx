#include "gx_xml_handler.hxx"

#include <iostream>
using std::cout;
using std::endl;
XmlHandler::XmlHandler()
{
    working    = TEquip();
    list       = NULL;
    metDataTag = false;
}

XmlHandler::~XmlHandler()
{
 /* dtor nada */
}

bool XmlHandler::startElement(const QString &namespaceURI, const QString &localName,
                  const QString &qName, const QXmlAttributes &attributes)
{
    (void)namespaceURI;
    (void)localName;
    if (!metDataTag && qName != "data") {
        errorStr = QObject::tr("There is no data block in the file.");
        return false;

    }
    if (qName == "data") {
        metDataTag = true;
    }
    else if (qName == "item") {
        working.canEnchant    =attributes.value("canEnchant").toInt();
        working.name          =attributes.value("name").toStdString();
        working.atk           =attributes.value("attack").toInt();
        working.def           =attributes.value("defense").toInt();
        working.sta           =attributes.value("sta").toInt();
        working.eng           =attributes.value("eng").toInt();
        working.hnr           =attributes.value("hnr").toInt();
        working.hlt           =attributes.value("htl").toInt();
        working.per           =attributes.value("perception").toInt();
        working.value_credits =attributes.value("value_credits").toInt();
        working.value_gold    =attributes.value("value_gold").toInt();
        working.proc_type     =attributes.value("proc_type").toInt();
        working.proc_rate     =attributes.value("proc_rate").toInt();
        working.rarity        =attributes.value("rarity").toInt();
    }
    currentText.clear();
    return true;
}

bool XmlHandler::endElement(const QString &namespaceURI, const QString &localName,
                const QString &qName)
{
    (void)namespaceURI;
    (void)localName;
    if (qName=="item")
    {
        list->push_back(working);
        working=TEquip();
    }else if(qName=="lore")
    {
        if (working.name!="")
        {
            working.lore=currentText.toStdString();
        }
    }else if (qName == "image")
    {
        if (working.name!="")
        {
            working.image_url=currentText.toStdString();
        }
    }else if (qName == "proc_desc")
    {
        if (working.name!="")
        {
            working.proc_desc=currentText.toStdString();
        }
    }else if (qName == "proc_name")
    {
        if (working.name!="")
        {
            working.proc_name=currentText.toStdString();
        }
    }
    return true;
}

bool XmlHandler::characters(const QString &str)
{
    currentText += str;
    return true;
}

bool XmlHandler::fatalError(const QXmlParseException &exception)
{
//    QMessageBox::information(NULL, QObject::tr("XML Error"),
//                             QObject::tr("Parse error at line %1, column %2:\n"
//                                         "%3")
//                             .arg(exception.lineNumber())
//                             .arg(exception.columnNumber())
//                             .arg(exception.message()));
    return false;
}

QString XmlHandler::errorString() const
{
    return errorStr;
}

void XmlHandler::link(eQuipList *p)
{
    list = p;
}

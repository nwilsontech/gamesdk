#pragma once


#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include <string>
#include <vector>
#include "gx_experiment.hxx"
#include <QXmlDefaultHandler>


typedef vector<TEquip> eQuipList;


class XmlHandler : public QXmlDefaultHandler
{
public:
    XmlHandler();
    ~XmlHandler();
    bool startElement(const QString &namespaceURI, const QString &localName,
                      const QString &qName, const QXmlAttributes &attributes) Q_DECL_OVERRIDE;
    bool endElement(const QString &namespaceURI, const QString &localName,
                    const QString &qName) Q_DECL_OVERRIDE;
    bool characters(const QString &str) Q_DECL_OVERRIDE;
    bool fatalError(const QXmlParseException &exception) Q_DECL_OVERRIDE;
    void link(eQuipList *p);
    QString errorString() const Q_DECL_OVERRIDE;
private:
    QString currentText;
    QString errorStr;
    eQuipList *list;
    TEquip working;
    bool   metDataTag;
};

#endif // XMLHANDLER_H

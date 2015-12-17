
#pragma once
#ifndef GX_EXPR_ITEM_READER_HXX
#define GX_EXPR_ITEM_READER_HXX

#include <QXmlStreamReader>
#include <string>
#include <vector>
#include "gx_experiment.hxx"




class XitemReader
{
public:
    XitemReader();
    bool read(QIODevice *device);
    void link(std::vector<TEquip> *p);
    void unlink(void);
private:
    void readi();
    void readItem();
    void readLore();
    void readProcDesc();
    void readProcName();
    void readImage();
    QXmlStreamReader xml;
    std::vector<TEquip> *pass;
protected:
    TEquip working;
};

#endif // GX_EXPR_ITEM_READER_HXX


#include "gx_expr_item_reader.hxx"
#include <iostream>
/**

**/
XitemReader::XitemReader(){pass=NULL;}

bool XitemReader::read(QIODevice *device)
{
    working = TEquip();
    xml.setDevice(device);

    if (xml.readNextStartElement()) {
        if (xml.name() == "data")
            readi();
        else
            xml.raiseError(QObject::tr("The file is not an XML version 1.0 file."));
    }

    return !xml.error();
}

void XitemReader::link(std::vector<TEquip> *p)
{
    pass = p;
}

void XitemReader::unlink(void)
{
    pass = NULL;
}

/** Begin Private **/
void XitemReader::readi()
{
    Q_ASSERT(pass!=NULL && xml.isStartElement() && xml.name() == "data");
    std::cout<<"{readi dbg}\n\n";

    while (xml.readNextStartElement()) {
        std::cout<<".]"<<xml.name().toString().toStdString()<<std::endl;
        if (xml.name() == "item")
        {
          readItem();
          pass->push_back(working);
          working = TEquip();
        }
        else  //readNextStartElement
            xml.skipCurrentElement();
    }
}

void XitemReader::readItem()
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "item");
    working.canEnchant    =xml.attributes().value("canEnchant").toInt();
    working.name          =xml.attributes().value("name").toString().toStdString();
    working.atk           =xml.attributes().value("attack").toInt();
    working.def           =xml.attributes().value("defense").toInt();
    working.sta           =xml.attributes().value("sta").toInt();
    working.eng           =xml.attributes().value("eng").toInt();
    working.hnr           =xml.attributes().value("hnr").toInt();
    working.hlt           =xml.attributes().value("htl").toInt();
    working.per           =xml.attributes().value("perception").toInt();
    working.value_credits =xml.attributes().value("value_credits").toInt();
    working.value_gold    =xml.attributes().value("value_gold").toInt();
    working.proc_type     =xml.attributes().value("proc_type").toInt();
    working.proc_rate     =xml.attributes().value("proc_rate").toInt();
    working.rarity        =xml.attributes().value("rarity").toInt();
    //std::cout<<working.name<<std::endl;

//    while(xml.readNextStartElement())
//    {
//        std::cout<<"  ]"<<xml.name().toString().toStdString()<<std::endl;
//        if(xml.name() == "item")
//        {
//            std::cout<<"Blah\n";
//        }else
//            xml.skipCurrentElement();
//    }

    while (xml.readNextStartElement()) {
        if (xml.name() == "lore")
            readLore();
        else if (xml.name() == "effect")
        {
            /*blah*/
        }
        else if (xml.name() == "proc_desc")
        {
            readProcDesc();
        }
        else if (xml.name() == "proc_name")
        {
            readProcName();
        }
//        else if (xml.name() == "image")
//        {
//            //readImage();
//            /*Issue Function*/
//        }
        else xml.skipCurrentElement();

    }


}


void XitemReader::readLore()
{
    //Q_ASSERT(xml.isStartElement() && xml.name() == "lore");
    xml.readElementText().toStdString();

    //std::cout<<xml.readElementText().toStdString()<<std::endl;
}

void XitemReader::readProcDesc()
{
    //Q_ASSERT(xml.isStartElement() && xml.name() == "proc_desc");
    working.proc_desc = xml.readElementText().toStdString();

    //std::cout<<xml.readElementText().toStdString()<<std::endl;

}

void XitemReader::readProcName()
{
    //Q_ASSERT(xml.isStartElement() && xml.name() == "proc_name");
    working.proc_name = xml.readElementText().toStdString();

    //std::cout<<xml.readElementText().toStdString()<<std::endl;

}
/*
 * There is some issue using this function!!!!!!!
 * */
void XitemReader::readImage()
{

    std::cout<<"..[Image]\n";
    //Q_ASSERT(xml.isStartElement() && xml.name() == "image");
    working.image_url = xml.readElementText().toStdString();
    while (xml.readNextStartElement()) {
        if (xml.name() == "female")
        {

        }
        else xml.skipCurrentElement();

    }
    //std::cout<<xml.name().toString().toStdString()<<std::endl;


}

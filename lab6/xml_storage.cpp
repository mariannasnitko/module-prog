#include "xml_storage.h"
#include <fstream>
#include <iostream>
#include <string>

#include <QString>
#include <QDebug>
#include <QFile>
#include <QtXml>

using namespace std;

Inventor domElementToInventor(QDomElement &element)
{
    Inventor inv;
    inv.id = element.attribute("id").toInt();
    inv.name = element.attribute("name").toStdString();
    inv.invention = element.attribute("invention").toStdString();
    inv.patents = element.attribute("patents").toInt();
    return inv;
}

Invention domElementToInvention(QDomElement &element)
{
    Invention inv;
    inv.id = element.attribute("id").toInt();
    inv.invent = element.attribute("invention").toStdString();
    inv.data = element.attribute("data").toStdString();
    inv.year = element.attribute("year").toInt();
    return inv;
}

QDomElement inventorToDomElement(QDomDocument &doc, Inventor & inv){

    QDomElement inventor_el = doc.createElement("inventors");
    inventor_el.setAttribute("id", inv.id);
    inventor_el.setAttribute("name", inv.name.c_str());
    inventor_el.setAttribute("invention", inv.invention.c_str());
    inventor_el.setAttribute("patents", inv.patents);
    return inventor_el;
}

QDomElement inventionToDomElement(QDomDocument &doc, Invention & inv){

    QDomElement invention_el = doc.createElement("inventions");
    invention_el.setAttribute("id", inv.id);
    invention_el.setAttribute("invention", inv.invent.c_str());
    invention_el.setAttribute("data", inv.data.c_str());
    invention_el.setAttribute("year", inv.year);
    return invention_el;
}

bool XmlStorage::load()
{
    string filename = this->dir_name_ + "/lections.xml";
    QString q_filename = QString::fromStdString(filename);
    QFile file(q_filename);
    bool isOpened = file.open(QFile::ReadOnly);
    if (!isOpened)
    {
        qDebug() << "file not opened " << q_filename;
        return false;
    }
    QTextStream ts(&file);
    QString text = ts.readAll();
    QDomDocument doc;
    QString errorMessage;
    int errorLine;
    int errorColumn;
    if (!doc.setContent(text,&errorMessage,&errorLine,&errorColumn))
    {
        qDebug() << "Error parsing XML text: " << errorMessage;
        qDebug() << "at line" << errorLine << ", column " << errorColumn;
        return false;
    }
    QDomElement root = doc.documentElement();
    for(int i = 0; i < root.childNodes().size(); i++)
    {
        QDomNode node = root.childNodes().at(i);
        QDomElement element = node.toElement();
        Inventor inv = domElementToInventor(element);
        this->inventors_.push_back(inv);
    }
    file.close();

    //---------------------------------------------------------

    string topicFilename = this->dir_name_ + "/inventions.xml";
    QString q_topicFilename = QString::fromStdString(topicFilename);
    QFile fileTF(q_topicFilename);
    bool isOpenedTF = fileTF.open(QFile::ReadOnly);
    if (!isOpenedTF)
    {
        qDebug() << "file not opened " << q_topicFilename;
        return false;
    }
    QTextStream tstf(&fileTF);
    QString textTF = tstf.readAll();
    QDomDocument docTF;
    QString errorMessageTF;
    int errorLineTF;
    int errorColumnTF;
    if (!docTF.setContent(textTF,&errorMessageTF,&errorLineTF,&errorColumnTF))
    {
        qDebug() << "Error parsing XML text: " << errorMessageTF;
        qDebug() << "at line" << errorLineTF << ", column " << errorColumnTF;
        return false;
    }
    QDomElement rootTF = docTF.documentElement();
    for(int i = 0; i < rootTF.childNodes().size(); i++)
    {
        QDomNode nodeTF = rootTF.childNodes().at(i);
        QDomElement elementTF = nodeTF.toElement();
        Invention invn = domElementToInvention(elementTF);
        this->inventions_.push_back(invn);
    }
    fileTF.close();
    return true;
}

bool XmlStorage::save()
{
    QDomDocument doc;
    QDomElement root = doc.createElement("inventors");
    for(Inventor & inv : this->inventors_)
    {
       QDomElement inventor_el = inventorToDomElement(doc, inv);
         root.appendChild(inventor_el);
    }
    doc.appendChild(root);
    QString xml_text = doc.toString(4);
    std::string filename = this->dir_name_ + "/inventors.xml";
    QString q_filename = QString::fromStdString(filename);
    QFile file(q_filename);
    bool isOpened = file.open(QFile::WriteOnly);
    if (!isOpened)
    {
        qDebug() << "file not opened " << q_filename;
        return false;
    }
    QTextStream ts(&file);
    ts << xml_text;
    file.close();

    //-------------------------------------------------

    QDomDocument docT;
    QDomElement rootT = docT.createElement("invention");
    for(Invention & invn : this->inventions_)
    {
       QDomElement invention_el = inventionToDomElement(doc, invn);
         rootT.appendChild(invention_el);
    }
    docT.appendChild(rootT);
    QString xml_textT = doc.toString(4);
    string filenameT = this->dir_name_ + "/inventions.xml";
    QString q_filenameT = QString::fromStdString(filenameT);
    QFile fileT(q_filenameT);
    bool isOpenedT = fileT.open(QFile::WriteOnly);
    if (!isOpenedT)
    {
        qDebug() << "file not opened " << q_filenameT;
        return false;
    }
    QTextStream tsT(&file);
    tsT << xml_textT;
    fileT.close();
    return false;
}

int XmlStorage::getNewInventorId()
{
    int max = 0;
    for (Inventor inv : this->inventors_)
    {
        if (max < inv.id)
            max = inv.id;
    }
    return max + 1;
}

int XmlStorage::getNewInventionId()
{
    int max = 0;
    for (Invention inv : this->inventions_)
    {
        if (max < inv.id)
            max = inv.id;
    }
    return max + 1;
}

vector<Inventor> XmlStorage::getAllInventors()
{
    return this->inventors_;
}

optional<Inventor> XmlStorage::getInventorById(int inventor_id)
{
    for (Inventor &inv : this->inventors_)
    {
        if (inv.id == inventor_id)
        {
            return inv;
        }
    }
    return nullopt;
}

bool XmlStorage::updateInventor(const Inventor &inventor)
{
    for (int i = 0; i < inventors_.size(); i++)
    {
        if (inventors_[i].id == inventor.id)
        {
            inventors_[i] = inventor;
            return 1;
        }
    }
    return 0;
}

bool XmlStorage::removeInventor(int inventor_id)
{
    for (int i = 0; i < inventors_.size(); i++)
    {
        if (inventors_[i].id == inventor_id)
        {
            inventors_.erase(inventors_.begin() + i);
            return 1;
        }
    }
    return 0;
}

int XmlStorage::insertInventor(const Inventor &inventor)
{
    Inventor inv = inventor;
    inv.id = getNewInventorId();
    inventors_.push_back(inv);
    return inv.id;
}

vector<Invention> XmlStorage::getAllInventions()
{
    return this->inventions_;
}

optional<Invention> XmlStorage::getInventionById(int inventor_id)
{
    for (Invention &inv : this->inventions_)
    {
        if (inv.id == inventor_id)
        {
            return inv;
        }
    }
    return nullopt;
}

bool XmlStorage::updateInvention(const Invention &invention)
{
    for (int i = 0; i < inventions_.size(); i++)
    {
        if (inventions_[i].id == invention.id)
        {
            inventions_[i] = invention;
            return 1;
        }
    }
    return 0;
}

bool XmlStorage::removeInvention(int invention_id)
{
    for (int i = 0; i < inventions_.size(); i++)
    {
        if (inventions_[i].id == invention_id)
        {
            inventions_.erase(inventions_.begin() + i);
            return 1;
        }
    }
    return 0;
}

int XmlStorage::insertInvention(const Invention &invention)
{
    Invention inv = invention;
    inv.id = getNewInventionId();
    inventions_.push_back(inv);
    return inv.id;
}

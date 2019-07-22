#ifndef TOOL_H
#define TOOL_H
#include<QString>
#include<QFile>
/*!
 * \brief cutFile
 * delete all lines that don't contain Txxxx,(sampling xxxx-th time ) from old file
 * add this reslut to the new file.
 *
 * \param oldFile file to be changed
 * \param destination new file
 * \param n n-th loop starting from 0
 * \param length: number of sample /loop
 * \param error error message
 * \return true if 0 error, false if there 's an error
 */
bool cutFile(QString oldFile , QString destination,int n,int length,QString &error );


/*!
 * \brief create create a file to keep tmp datas
 * if the file exists , clear it and
 * otherwise creates a new file
 * \param fileName
 * \param error
 * \return
 */
QFile* create(QString fileName,QString &error);


#endif // TOOL_H

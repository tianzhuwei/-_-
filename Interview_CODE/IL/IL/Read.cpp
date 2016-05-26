#include "Read.h"

Read::Read(void)
{
	CFile destFile;//�ļ��򿪶���;
	CFileException ex;//������Ϣ�ռ�;
	mycmap.InitHashTable(41);//��CMAP���г�ʼ��;

	CString strProcessed, strWordLabel, strKeyword, strLabel,strListLength,strFirst,strComp;
	int i,nPos,nStart,nEnd,nListLength,nListLenIter,nStartIn,nEndIn,nSize,nComp;
	int count=0;
	int * pLabel;

	CArray<int *, int *> * pDFDeweyList;

	CString strFile="F:\\weitianzhu\\����\\IL\\data\\dblp.txt";
	//CString strFile="C:\\Users\\weitianzhu\\Desktop\\IL\\data\\xmark5.txt";
	//CString strFile="C:\\Users\\weitianzhu\\Desktop\\IL\\data\\dblp.txt";
	//CString strFile="C:\\Users\\weitianzhu\\Desktop\\IL\\data\\dblp2.txt";
	
	//CString strFile="F:\\IndexTxt\\xmark5.txt";
	//CString strFile="D://xmark500.txt";6
	if (!destFile.Open(((LPCTSTR)strFile),CFile::modeRead,&ex)){//������ܴ������������Ϣ;
		TCHAR szError[1024];
		ex.GetErrorMessage(szError, 1024);
		cout << "Couldn't open source file: ";
		cout << szError;
		return;
	}

	//���ؼ��ֽ��б������;
	while(1) //each time read a keyword and all its labels
	{
		if(strProcessed.Find('>') == -1)	//�Ҳ��� '>' �Ļ���ִ�и����;
		{
			if(!SetBuffer(strProcessed, 1024, destFile))//�ڴ��ļ����󣬶�ȡ����֮ǰ������setbuffer���������������ļ����Ļ�������
				////����strProcessedΪָ�����ļ���,����BUFFERSIZEΪ��������С,����destFileָ���Զ��Ļ�������ʼ��ַ��
			{
				break;
			}
		}

		nPos = strProcessed.Find('>');//����'>'����������һ���ַ�������Ϊ0;
		strWordLabel = strProcessed.Left(nPos);//ȡ�����������npos���ַ�;
		strProcessed = strProcessed.Mid(nPos+1);//ȡ���������ӵ�npos��ʼ���ַ�;
		strProcessed.Trim();//ɾ���ո�;

		//ȥ��<>;
		strWordLabel.TrimLeft('<');//����߿�ʼɾ��<��ֱ����ƥ��;
		strWordLabel.TrimRight('>');//���ұ߿�ʼɾ��>��ֱ����ƥ��;

		//ȡ���ؼ���;
		nStart = 0;
		nEnd = strWordLabel.Find(':');//��һ��������������ǰ�ǹؼ��֣�;
		strKeyword = strWordLabel.Mid(nStart, nEnd-nStart);//Left(nPos);���ؼ��ָ���strKeyword 
		mycmap.operator[](strKeyword);//���ؼ��ֱ�����CMap;
		cout<<++count;
		wcout<<(LPCTSTR)strKeyword<<endl;

		//ȡ���ؼ��ֵĸ���,����CArray�ĳ��ȣ�= �ؼ��ֵĸ�����;
		nStart = nEnd + 1;

		nEnd = strWordLabel.Find(':', nStart);//�ڶ���������������ǰ�Ǵ˹ؼ��ֶ�Ӧ�ı��������;
		strListLength = strWordLabel.Mid(nStart, nEnd-nStart);//Left(nPos); //list length�������������strListLength
		nStart = nEnd + 1;

		nListLength = _ttoi(strListLength);//�ַ���ת����������,�����ؼ��ֵı������ת��Ϊ����;

		if(mycmap.Lookup(strKeyword, pDFDeweyList))//�ڹ�ϣ���в��ҹؼ��֣������ڣ�����pDFDeweyList
		{
			pDFDeweyList = new CArray<int *, int *>;
			pDFDeweyList->SetSize(nListLength);//����ָ�����飬����ΪnListLength
			mycmap[strKeyword] = pDFDeweyList;
		}
		else
		{
			cout << "error" << endl;
		}

		//�������;
		nListLenIter = 0;

		//read all its labels
		while(nStart < strWordLabel.GetLength() )//����strWordLabel���ֽڸ���������һ���ؼ��ֵ�ȫ������
		{
			//ȡ��һ������;
			nEnd = strWordLabel.Find(';', nStart);
			strLabel = strWordLabel.Mid(nStart, nEnd-nStart);//Left(nPos);ȡ����һ�α���
			nStart = nEnd + 1;//����ѭ��;

			//construct the hash mapping between each id and the corresponding label

			//the first number
			nStartIn = 0;
			nEndIn = strLabel.Find('.');
			strFirst = strLabel.Mid(nStartIn, nEndIn-nStartIn);//Left(nPos);ȡ����һС�α�������ָ���
			nStartIn = nEndIn + 1;

			//nSize���ڱ��볤��
			nSize = _ttoi(strFirst); //notice the first label: site.1.1, which should be processed specially����һ�α�������ָ���תΪ����
			pLabel = new int[nSize+1];//�����ڴ�
			(*pDFDeweyList)[nListLenIter] = pLabel;//nListLenIterΪ*pDFDeweyList������
			nListLenIter ++;

			i = 0;
			pLabel[i] = nSize;//��0��λ�ô洢����ĳ���
			i ++;

			//����ȡ��һ�����ı���;
			while(nStartIn < strLabel.GetLength())//��ȡ��һС�α���;
			{
				if(strLabel.Find('.', nStartIn) == -1)
				{
					nComp = _ttoi(strLabel.Mid(nStartIn));//�ӱ���ĵ�һ�����ֿ�ʼתΪ����;
					pLabel[i] = nComp;//���δ洢���ָ���;
					i++;
					nStartIn = strLabel.GetLength();
				}
				else
				{
					nEndIn = strLabel.Find('.', nStartIn);
					strComp = strLabel.Mid(nStartIn, nEndIn-nStartIn);//Left(nPos);
					nStartIn = nEndIn + 1;

					nComp = _ttoi(strComp);

					pLabel[i] = nComp;
					i++;
				}
			}

			ASSERT(i == nSize+1);

			//construct the hash mapping between each keyword and its DFDewey label list
		}


	}//while;
	destFile.Close();
}//end;

Read::~Read(void){

}

BOOL Read::SetBuffer(CString& strBuf, int nBreakPos, CFile& destFile){//�����ļ����Ļ�������С;
					 //����ʼ��ַ����������С��ָ�����ļ�����;
	char pbuf[1024]={0};			//256K each time
	CString strTail;
	long nRead = 0;
	CString strTemp;

	memset(pbuf, 0, 1024);//��pbuf��ǰBUFFERSIZE���ֽ��û�Ϊ0

	nRead= destFile.Read(pbuf, 1024-1);  //���ļ�����BUFFERSIZE-1���ַ�����pbuf������ʵ�ʶ�ȡ�����ַ������256K

	strTemp = pbuf;  //������������ת��ΪCString����

	strTemp = strBuf + strTemp;//ʲô��˼������;

	strTemp.Trim();//����ո�;

	//to the end of the file
	if(strTemp.GetLength() == 0)
	{
		return FALSE;
	}

	//contains a keyword and all its labels or ids
	if(strTemp.Find('>') != -1)//���ļ����д���'>';
	{
		strBuf = strTemp;//���ļ�������strBuf
		return TRUE;
	}
	else 
	{
		strBuf = strTemp;
		while(1)
		{
			memset(pbuf, 0, 1024);//��������һ���ڴ�������ĳ��������ֵ�����ǶԽϴ�Ľṹ�������������������һ����췽��;
			nRead= destFile.Read(pbuf, 1024-1);
			strTemp = pbuf;
			strBuf += strTemp;

			if(strTemp.Find('>') != -1)
			{
				return TRUE;
			}
		}
	}

	return TRUE;
}
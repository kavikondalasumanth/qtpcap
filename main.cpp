#include "qtpcap.h"
/*********************************************************
* ����:
* ����ǳ���ĺ��Ĳ��֣�������ݰ��Ľػ�
* ����:
* pParam: �û�ѡ��������������ݵ�����������
*********************************************************/
int CaptureThread(LPVOID pParam)
{
    const char* pCardName=(char*)pParam; // ת�������������������
    pcap_t* adhandle;
    char errbuf[PCAP_ERRBUF_SIZE];
    // ����������������Ϊ����ģʽ
    adhandle=pcap_open_live(pCardName,65535,1,1000,errbuf);
    pcap_dumper_t* dumpfile;
    // �����洢�����������ݰ����ļ�
    dumpfile=pcap_dump_open(adhandle, "packet.dat");
    int re;
    pcap_pkthdr* header; // Header
    u_char* pkt_data; // ���ݰ�����ָ��
    // �����������ļ��в�ͣ��ȡ���ݰ���Ϣ
    while((re=pcap_next_ex(adhandle,&header,(const u_char**)&pkt_data))>=0)
    {
        // ����������ݰ������ļ�
        pcap_dump((unsigned char*)dumpfile,header,pkt_data);
    }
    return 0;
}

int main(int argc, char **argv)
{
    pcap_if_t* alldevs;
    pcap_if_t* d;
    char errbuf[PCAP_ERRBUF_SIZE];
    char ** devName;
    pcap_findalldevs(&alldevs,errbuf); // ��������豸ָ��
    int devIndex=0;
    for(d=alldevs;d;d=d->next) // ö������Ȼ����ӵ�ComboBox��
    {
        devIndex++;
        printf("%d,%s,%s\n",devIndex,d->description,d->name);  // d->name����������Ҫ�����������ַ���
        devName[devIndex]=d->name;  // �Լ�����Ҫ���浽�����Ӧ������ȥ
    }
    int i;
    printf("������һ�����֣����Իس�������\n");
    scanf("%d",&i);
    printf("%s\n",devName[i]);
    CaptureThread(devName[i]);
}




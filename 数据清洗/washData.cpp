#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;
class Graph{
public:
	int target;//Ŀ����
	int startT;//����ʱ��
	int dur;// ����ʱ��
	int neiId; //�����ھӵ�id
	int mark;//�������Ψһ��ʶ��
	Graph(){
		target = 0;
		startT = 0;
		dur = 0;
		neiId = 0;
		mark = 0;
	}
};
bool cmp(Graph g1, Graph g2){
	return g1.target < g2.target;
}
void main()
{
	int MARK = 0; //�������Ψһ��ʶ��

	fstream read;
	read.open("austin.txt", ios::in);
	/*
		��һ�� ���е�վ���� ���е���·���� ������·��վ��� �ܵ�������
		�ڶ��� ��·id
		������ ������·;��վ��id
		������ վ��id
		������ ������·һ����10�೵
	*/
	int Size;
	read >> Size;
	vector<vector<Graph>> route;
	vector<int> index; //��¼ÿ����ĳ����ھӸ���
	route.resize(Size);
	index.resize(Size);
	int loop;
	read >> loop; //һ����loop����·
	int tmp;
	read >> tmp;
	read >> tmp;
	//    ��һ�����ݶ���
	for (int i = 0; i < loop; i++){
		int id;
		read >> id;
		//	�ڶ������ݶ���
		int site; // վ����
		read >> site;
		//	���������ݶ���
		vector<int> tmpSite;
		tmpSite.resize(site);
		for (int j = 0; j < site; j++){
			int site_id;
			read >> site_id;
			//tmpSite.push_back(site_id);
			tmpSite[j] = site_id;

			//	���������ݶ���
			//  ���������е�id���

		}
		int fre;// һ����fre�����
		read >> fre;
		//	���������ݶ���
		for (int j = 0; j < fre; j++){ // 10��

			for (int n = 0; n < site - 1; n++){ //��ʼ��������С,���ҽ�����id��ֵ���õ�
				int extendSize = route[tmpSite[n]].size() == 0 ? 1 : route[tmpSite[n]].size() + 1;
				route[tmpSite[n]].resize(extendSize);
				route[tmpSite[n]][extendSize - 1].neiId = tmpSite[n + 1];
			}



			int arrival, start;
			read >> arrival; //��ʼ��ĵ�������
			for (int k = 0; k < site-1; k++){ //siteվ��

				read >> start; //��һ�е�ĩ
				route[tmpSite[k]][route[tmpSite[k]].size()-1].startT = start;
				route[tmpSite[k]][route[tmpSite[k]].size() - 1].target = tmpSite[k + 1];
				read >> arrival; //�ڶ��еĳ�
				//read.seekp(-1, ios_base::cur);
				route[tmpSite[k]][route[tmpSite[k]].size() - 1].dur = arrival - start;
				route[tmpSite[k]][route[tmpSite[k]].size() - 1].mark = MARK;
			}
			read >> start; //���һ������
			MARK++;
		}
	}
	cout << "building down!" << endl;
	read.close();

	
	for (int i = 0; i < route.size(); i++){
		for (int j = 0; j < route[i].size(); j++)
			sort(route[i].begin(),route[i].end(),cmp);
	}
	cout << " sort down!" << endl;
	fstream write;
	write.open("scc.txt", ios::out);
	write << Size <<endl;
	for (int i = 0; i < Size; i++){
		write << i << "  ";//��������
		//write << route[i].size() << "  ";//����ھӽ��ĸ���
		//for (int j = 0; j < route[i].size(); j++){
		//	write << route[i][j].target<<"  "<<
		//}
		vector<int> sumSize; //�ֽ�� ����ÿ����ĩ�����ھӵ��±�
		int neiNum = 0; //��������ھӵĸ���
		vector<int> neiId;//�����ھӵ�id
		sumSize.resize(1);
		neiId.resize(1);
		if (route[i].size() == 0){
			write << 0 << endl;
			continue;
		}
		for (int j = 0; j < route[i].size() -1 ; j++){
			if (route[i][j].target != route[i][j + 1].target)
			{
				neiNum++;
				sumSize[sumSize.size() - 1] = j+1;
				sumSize.resize(sumSize.size() + 1);
				
				neiId[neiId.size() - 1] = route[i][j].target;
				neiId.resize(neiId.size() + 1);
			}
		}
		if (neiNum == 0){ //����ֻ��һ���������
			neiNum++;
			sumSize[0] = route[i].size();
			neiId[0] = route[i][0].target;
		}
		else if (neiNum != 0){ //������ֲ�ͬ�����洢���һ�����
			neiNum++;
			sumSize[sumSize.size() - 1] = route[i].size();
			neiId[neiId.size() - 1] = route[i][route[i].size() - 1].target;
		}
		write << neiNum << "  "; //����ھӵĸ���
		for (int j = 0; j < neiNum; j++){
			write << neiId[j] << "  ";//����ھӽ���id
			int sum = j == 0 ? 0 : sumSize[j - 1];
			int goNei = sumSize[j] - sum;
			write << goNei << "  "; //�ж��ٱ�ȥ�ھӵ�
			for (int k = sum; k < sumSize[j]; k++){
				write << route[i][k].dur << "  " << route[i][k].startT << "  " << route[i][k].mark << "  ";
				// ·�������ѵ�ʱ�� ͼ�бߵ�Ȩֵ ������Ψһid
			}
			write << endl;
		}
		write << endl;
	}
	
}
/*
	ÿһ����· ��������վ��i������Ϊ 1 �� ����
*/
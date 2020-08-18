#include<iostream>
#include<ctime>
#include<vector>
#include<random>
#include<fstream>
#include<string>

using namespace std;




class Perceptron
{
public:
	
	//��� ����� �迭�� �̿��ؼ� �ϰڴ�..
	vector < vector<double>> input;
	vector< vector<vector<double>>> weight; // 3���� weight ���� ����...[layer][out][in] �̷������� �����̴�.
	vector< vector<vector<double>>> net;    // 3���� net ���� ���� ....[input_row][node_row][node_col].... input�� ����� ������ �ش��ϴ� net���� ���� �� �����ϱ� ���Ѱ�
	vector< vector<double>> theta; //theta�� ���� 2���� ���� ����..... [node_row][node_col]...... �� ����� f(net) �Ҷ� �ʿ��� theta�� ���� �迭.... 
	vector< vector<vector<double>>> fnet; // net���� theta���� ũ�ų� ������ 1 ������ 0  .....[input_row][node_row][node_col]
	vector< vector<vector<double>>> delta;     //delta�� �����ϰٴ�.   [input_row][node_row][node_col]
	vector<int> colPerNodeNumber;  //column�� ����� ������ ���� ���̴�
	vector<double> output;        // ������ ��忡 �ش��ϴ� output ���� �Է� ��츶�� ���� �ϰڴ�.
	vector<int> target_arr;       // target�� �Ǵ� ���� �����ϴ� �迭�� ����ڴ�.
	



	int input_row;           //�Է� ����� ��
	int input_col;           //�Է��� ����
	int layer;               // ���� ¥�� �ΰ�
	int layerPerNodeNum;     //layer�� node�� ����
	int node_row;            // �ش� ����� row
	int node_col;            // node_col == layer + 1 
	int errorNum;
	double c = 3;
public:
	
	

	
	Perceptron()
	{

	}
	
	
	//n�� input node�� ����
	//layer
	//layerPerNodeNum layer�� node�� ����
	Perceptron(int n, int layer, int layerPerNodeNum)
	{
		this->input_row = (int)pow(2, n);
		this->input_col = n;
		this->layer = layer;
		this->layerPerNodeNum = layerPerNodeNum;

		//input 2���� �迭 ����
		for (int i = 0; i < input_row; i++)
		{
			vector<double> element;
			element.resize(input_col);
			input.push_back(element);
		}

		int temp = 0;
		for (int i = 0; i < input.size(); i++)
		{
			for (int j=0; j<input[i].size(); j++)
			{
				if ((temp >> j) % 2 == 1)
				{
					input[i][input[i].size()-1-j] = 1;
				}
			}
			temp++;
		}


		//�� ������ ����� ������ �����ϴ� colPerNodeNumber�� �Է��ϴ� ��
		colPerNodeNumber.resize(layer + 1 , 0);
		colPerNodeNumber[0] = input_col;
		colPerNodeNumber[layer] = 1;
		for (int i = 1; i < layer; i++)
		{
			colPerNodeNumber[i] = layerPerNodeNum;
			
			
		}

		
		//n �� layerPerNodeNum�߿� ū�� ��󳻱�
		int max_n_layerPerNodeNum;

		if (n > layerPerNodeNum)
			max_n_layerPerNodeNum = n;
		else
			max_n_layerPerNodeNum = layerPerNodeNum;

		this->node_row = max_n_layerPerNodeNum;
		this->node_col = layer+1;
		


		//weight 3���� vector �������� �о�־ ���� ����
		//���� perceptron�� ��쿡 [1][input_col][1]
		if (layer == 1)
		{
			vector<vector<double>> element2;

			for (int j = 0; j < input_col; j++)
			{
				vector<double> element1;
				element1.resize(1);
				element2.push_back(element1);
			}
			weight.push_back(element2);

		}
		else
		{
			vector<vector<double>> element2;

			for (int j = 0; j < input_col; j++)
			{
				vector<double> element1;
				element1.resize(layerPerNodeNum);
				element2.push_back(element1);
			}
			weight.push_back(element2);

			for (int i = 1; i < layer - 1; i++)
			{
				vector<vector<double>> element2;

				for (int j = 0; j < layerPerNodeNum; j++)
				{
					vector<double> element1;
					element1.resize(layerPerNodeNum);
					element2.push_back(element1);
				}
				weight.push_back(element2);
			}


			vector<vector<double>> element3;

			for (int j = 0; j < layerPerNodeNum; j++)
			{
				vector<double> element1;
				element1.resize(1);
				element3.push_back(element1);
			}
			weight.push_back(element3);


		}



		//net 3���� vector �������� �о�־ ���� ����
		for (int i = 0; i < input_row; i++)
		{
			vector<vector<double>> element2;
			for (int j = 0; j < max_n_layerPerNodeNum; j++)
			{
				vector<double> element1;
				element1.resize(layer+1);
				element2.push_back(element1);
			}
			net.push_back(element2);
		}

		//theta 2���� �迭 ���� Ȯ��
		for (int i = 0; i < max_n_layerPerNodeNum; i++)
		{
			vector<double> element;
			element.resize(layer+1);
			theta.push_back(element);
		}

		//fnet 3���� �迭 ���� Ȯ��
		for (int i = 0; i < input_row; i++)
		{
			vector<vector<double>> element2;
			for (int j = 0; j < max_n_layerPerNodeNum; j++)
			{
				vector<double> element1;
				element1.resize(layer + 1);
				element2.push_back(element1);
			}
			fnet.push_back(element2);
		}

		//delta 3���� �迭 ���� ����
		for (int i = 0; i < input_row; i++)
		{
			vector<vector<double>> element2;
			for (int j = 0; j < max_n_layerPerNodeNum; j++)
			{
				vector<double> element1;
				element1.resize(node_col);
				element2.push_back(element1);
			}
			delta.push_back(element2);
		}

		output.resize(input_row);
		target_arr.resize(input_row);

	}

	//input�� 0,1 �ܿ��� �ִ� ���..
	Perceptron(int n, int n_row , int layer, int layerPerNodeNum)
	{
		this->input_row = n_row;
		this->input_col = n;
		this->layer = layer;
		this->layerPerNodeNum = layerPerNodeNum;

		

		//input 2���� �迭 ����
		for (int i = 0; i < input_row; i++)
		{
			vector<double> element;
			element.resize(input_col);
			input.push_back(element);
		}

		
		//�� ������ ����� ������ �����ϴ� colPerNodeNumber�� �Է��ϴ� ��
		colPerNodeNumber.resize(layer + 1, 0);
		colPerNodeNumber[0] = input_col;
		colPerNodeNumber[layer] = 1;
		for (int i = 1; i < layer; i++)
		{
			colPerNodeNumber[i] = layerPerNodeNum;


		}


		//n �� layerPerNodeNum�߿� ū�� ��󳻱�
		int max_n_layerPerNodeNum;

		if (n > layerPerNodeNum)
			max_n_layerPerNodeNum = n;
		else
			max_n_layerPerNodeNum = layerPerNodeNum;

		this->node_row = max_n_layerPerNodeNum;
		this->node_col = layer + 1;



		//weight 3���� vector �������� �о�־ ���� ����
		//���� perceptron�� ��쿡 [1][input_col][1]
		if (layer == 1)
		{
			vector<vector<double>> element2;

			for (int j = 0; j < input_col; j++)
			{
				vector<double> element1;
				element1.resize(1);
				element2.push_back(element1);
			}
			weight.push_back(element2);

		}
		else
		{
			vector<vector<double>> element2;

			for (int j = 0; j < input_col; j++)
			{
				vector<double> element1;
				element1.resize(layerPerNodeNum);
				element2.push_back(element1);
			}
			weight.push_back(element2);

			for (int i = 1; i < layer - 1; i++)
			{
				vector<vector<double>> element2;

				for (int j = 0; j < layerPerNodeNum; j++)
				{
					vector<double> element1;
					element1.resize(layerPerNodeNum);
					element2.push_back(element1);
				}
				weight.push_back(element2);
			}


			vector<vector<double>> element3;

			for (int j = 0; j < layerPerNodeNum; j++)
			{
				vector<double> element1;
				element1.resize(1);
				element3.push_back(element1);
			}
			weight.push_back(element3);


		}



		//net 3���� vector �������� �о�־ ���� ����
		for (int i = 0; i < input_row; i++)
		{
			vector<vector<double>> element2;
			for (int j = 0; j < max_n_layerPerNodeNum; j++)
			{
				vector<double> element1;
				element1.resize(layer + 1);
				element2.push_back(element1);
			}
			net.push_back(element2);
		}

		//theta 2���� �迭 ���� Ȯ��
		for (int i = 0; i < max_n_layerPerNodeNum; i++)
		{
			vector<double> element;
			element.resize(layer + 1);
			theta.push_back(element);
		}

		//fnet 3���� �迭 ���� Ȯ��
		for (int i = 0; i < input_row; i++)
		{
			vector<vector<double>> element2;
			for (int j = 0; j < max_n_layerPerNodeNum; j++)
			{
				vector<double> element1;
				element1.resize(layer + 1);
				element2.push_back(element1);
			}
			fnet.push_back(element2);
		}

		//delta 3���� �迭 ���� ����
		for (int i = 0; i < input_row; i++)
		{
			vector<vector<double>> element2;
			for (int j = 0; j < max_n_layerPerNodeNum; j++)
			{
				vector<double> element1;
				element1.resize(node_col);
				element2.push_back(element1);
			}
			delta.push_back(element2);
		}

		output.resize(input_row);
		target_arr.resize(input_row);

	}

	void random_initialize()
	{
		//srand((unsigned int)time(NULL)); //���尪 ����

		mt19937 random((random_device()()));
		uniform_real_distribution<double> dist(-1, 1);

		//weight �� random ����

		for (int i = 0; i < weight.size(); i++)
		{
			for (int j = 0; j < weight[i].size(); j++)
			{
				for (int k = 0; k < weight[i][j].size(); k++)
				{
					weight[i][j][k] = dist(random);
				}
			}
		}



		//theta �� random ����
		for (int i = 0; i < node_col; i++)
		{
			if (i == 0)
			{

			}
			else if (i != node_col - 1)
			{
				for (int j = 0; j < layerPerNodeNum; j++)
				{
					theta[j][i] = dist(random);
				}
			}
			else
			{
				theta[0][i] = dist(random);
			}
		}
	}

	void net_fun(int input_row_Number , int node_column_Number)
	{
		double temp;

		//input���� net���� ����
		if(node_column_Number == 1) 
		{ 
			//out
			for (int i = 0; i < colPerNodeNumber[node_column_Number]; i++)
			{
				temp = 0;

				//in
				for (int j = 0; j < colPerNodeNumber[node_column_Number - 1]; j++)
				{
					temp += weight[node_column_Number - 1][j][i] * input[input_row_Number][j];
				}
				net[input_row_Number][i][1] = temp + theta[i][1];
			}
		}
		//layerPerNode���� �� ���� net���� ����
		else if(node_column_Number > 1)
		{
			
			for (int i = 0; i < colPerNodeNumber[node_column_Number]; i++)
			{
				temp = 0;

				
				for (int j = 0; j < colPerNodeNumber[node_column_Number - 1]; j++)
				{
					temp = temp + (weight[node_column_Number - 1][j][i] * fnet[input_row_Number][j][node_column_Number - 1]);
				}
				net[input_row_Number][i][node_column_Number] = temp + theta[i][node_column_Number];
			}
		}

		
	}


	//w3 = -theta�� ����ؼ� �ñ׸��̵� ������ �Լ�
	double F_sigmoid(double net )
	{
		
		return ( 1 / (1 + exp(-net))); // sigmoid
		
	}

	//activation function�� �ñ׸��̵�� �ϰڴ�
	//net �ϰ� �� ������ Ȱ���Լ��� �־ ���� �����ϴ� �Լ�
	void fnet_fun(int input_row_Number, int node_column_Number)
	{
		for (int i = 0; i < colPerNodeNumber[node_column_Number]; i++)
		{

			fnet[input_row_Number][i][node_column_Number] = F_sigmoid(net[input_row_Number][i][node_column_Number]);
			
		}
	}
	

	//net �ϰ� f(net)�� �ѹ��� ���ִ�
	void UpStream()
	{
		for(int j = 0; j < input_row; j++)
		{
			for (int i = 1; i <= layer; i++)
			{

				net_fun(j, i);

				fnet_fun(j, i);

			}
			output[j] = fnet[j][0][layer];
		}
		
	}


	//Error �� ������ �˷���
	void errorNum_fun(int* targerArray)
	{
		int n = 0;
		for (int i = 0; i < input_row; i++)
		{
			if (targerArray[i] - output[i] < 0.2 && targerArray[i] - output[i] > -0.2)
			{

			}
			else
			{
				n++;
			}
		}
		errorNum = n;
		
	}


	// ��� �� ������ delta�� �ڿ��� ���� ����� �ִ� �Լ� 
	void delta_fun(int input_row_Number , int node_column_Number , int* target_array)
	{
		if (node_column_Number == layer)
		{
			//delta = -(t-o)*(1-f(net))*(f(net)) 
			//f'(net) = (1-f(net)) * f(net)
			delta[input_row_Number][0][layer] = -((double)target_array[input_row_Number] - fnet[input_row_Number][0][node_column_Number]) * (1-fnet[input_row_Number][0][node_column_Number]) * (fnet[input_row_Number][0][node_column_Number]);
			
		}
		else
		{
			double temp;
			// delta = f'(net) * (�ñ׸� delta * weight)
			for (int i = 0; i < colPerNodeNumber[node_column_Number]; i++)
			{
				temp = 0;

				for (int j = 0; j < colPerNodeNumber[node_column_Number + 1]; j++)
				{
					temp += delta[input_row_Number][j][node_column_Number + 1] * weight[node_column_Number][i][j];
					
					
					
				}
				delta[input_row_Number][i][node_column_Number] = temp * (1 - fnet[input_row_Number][i][node_column_Number])*(fnet[input_row_Number][i][node_column_Number]);
			}
		}
	}

	//layer Level ������ learning ���� ����
	void learning(int input_row_Number , int* target_array)
	{

		int temp = 0;

		if (target_array[input_row_Number] == 0)
		{
			if (output[input_row_Number] < 0.2)
				return;
		}
		else if (target_array[input_row_Number] == 1)
		{
			if (output[input_row_Number] > 0.8)
				return;
		}
		

		for (int i = 0; i < layer; i++)
		{
			if (i == 0)
			{
				for (int j = 0; j < colPerNodeNumber[0]; j++)
				{
			
					for (int k = 0; k < colPerNodeNumber[1]; k++)
					{
						weight[i][j][k] +=  + (-c) * delta[input_row_Number][k][1] * input[input_row_Number][j];   // ��weight = (-c) * delta * x ;

					}	
				}

				for (int j = 0; j < colPerNodeNumber[1]; j++)
				{
					theta[j][1] += (-c) * delta[input_row_Number][j][1];
				}
				
			}
			else
			{
				for (int j = 0; j < colPerNodeNumber[i]; j++)
				{
					for (int k = 0; k < colPerNodeNumber[i+1]; k++)
					{
						weight[i][j][k] += (-c) * delta[input_row_Number][k][i+1] * fnet[input_row_Number][j][i];   // ��weight = (-c) * delta * x ;

					}
				}

				for (int j = 0; j < colPerNodeNumber[i+1]; j++)
				{
					theta[j][i+1] += (-c) * delta[input_row_Number][j][i+1];
				}
			}

		}
		
	}


	//delta�� ���ϴ� ���� �ѹ���
	void BackStream(int input_row_Number,int* target_array)
	{
		for (int i = layer; i > 0; i--)
		{
			delta_fun(input_row_Number, i, target_array);
		}

		
	}


	//�������� �н��� �����ϰ� �� �Ŀ� �迭�鿡 ����ִ� ���� �����ֱ����� ��
	void view()
	{
		cout << "=======================================" << endl;

		cout << "input array:" << endl;
		for (int i = 0; i < input_row; i++)
		{
			for (int j = 0; j < input_col; j++)
			{
				cout << input[i][j] << " ";
			}
			cout << endl;
		}
		cout << "=======================================" << endl;
		cout << "weight" << endl;
		for (int i = 0; i < weight.size(); i++)
		{
			cout << "Layer : " << i << endl;
			for (int j = 0; j < weight[i].size(); j++)
			{
				cout << "out: " << j<<endl ;
				for (int k = 0; k < weight[i][j].size(); k++)
				{
					cout << "       in: " << weight[i][j][k] << endl;
				}
				cout << endl;
			}
			cout << "\n" << endl;
		}
		cout << "=======================================" << endl;
		cout << "theta = w3��� ���� " << endl;
		for (int i = 0; i < theta.size(); i++)
		{
			for (int j = 0; j < theta[i].size(); j++)
			{
				cout << theta[i][j] << "  ";
			}
			cout << endl;
		}

		cout << "=======================================" << endl;

		cout << "output: " << endl;
		for (int i = 0; i < output.size(); i++)
		{
			cout << output[i] << " ";
		}
		cout << endl;
		cout << "=======================================" << endl;
		
		cout << "net :" << endl;
		for (int i = 0; i < net.size(); i++)
		{
			cout << "input_row : " << i << " �� ��쿡" << endl;
			for (int j = 0; j < net[i].size(); j++)
			{
				for (int k = 0; k < net[i][j].size(); k++)
				{
					cout << net[i][j][k] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		cout << "=======================================" << endl;

		cout << "fnet :" << endl;
		for (int i = 0; i < fnet.size(); i++)
		{
			cout << "input_row : " << i << " �� ��쿡" << endl;
			for (int j = 0; j < fnet[i].size(); j++)
			{
				for (int k = 0; k < fnet[i][j].size(); k++)
				{
					cout << fnet[i][j][k] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}

		for (int i = 0; i < delta.size(); i++)
		{
			cout << " input_row : " << i << "�� ���� delta" << endl;
			for (int j = 0; j < delta[i].size(); j++)
			{
				for (int k = 0; k < delta[i][j].size(); k++)
				{
					cout << delta[i][j][k] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}

	}

	void weightView()
	{
		
		
		
	}

	
};


int main()
{

	//target �迭 ����
	int target_AND_Gate[4] = { 0,0,0,1 };
	int target_OR_Gate[4] = { 0,1,1,1 };
	int target_XOR_Gate[4] = { 0,1,1,0};
	int target_dounut_arr[9] = { 0,0,0,0,0,0,0,0,1 };
	int n;
	int tempNum; // ���� ����Ʈ�� �н��� ���ϴ°��� �Է� ���� ���̴�

	cout << "Which Gate do you want? select Gate" << endl;
	cout << "If you want AND_GATE input number 1 " << endl;
	cout << "If you want OR_GATE input number 2 " << endl;
	cout << "If you want XOR_GATE input number 3 " << endl;
	cout << "If you want dounut  input number4" << endl;
	cout << "Input number : ";
	cin >> tempNum;

	//�ð�ȭ�� �ʿ��� ���� �����
	/*
	ofstream out1("C:\\Users\\��ȯ��\\Desktop\\�����\\test1.csv");
	ofstream out2("C:\\Users\\��ȯ��\\Desktop\\�����\\test2.csv");
	ofstream out3("C:\\Users\\��ȯ��\\Desktop\\�����\\test3.csv");
	ofstream out_err("C:\\Users\\��ȯ��\\Desktop\\�����\\error.csv");
	string buffer;
	*/

	//��ü ����
	Perceptron p;


	A:
	switch (tempNum)
	{
	case 1:
		

		//AND_GATE
		p = Perceptron(2,1,2);
		p.random_initialize();
		p.UpStream();
		p.errorNum_fun(target_AND_Gate);
		p.view();

		//���� �����
		//out1 << p.weight[0][0][0] << "," << p.weight[0][1][0] << ", " << p.theta[0][1] << "\n";
		
		if (p.errorNum == 0)
		{
			p.view();
			cout << "congraturation!" << endl;
			return 0;
		}
		else
		{
			n = 0;
			while (1)
			{
				cout << n + 1 << "��° learning..." << endl;
				p.BackStream(n % 4, target_AND_Gate);
				p.learning(n % 4, target_AND_Gate);
				p.UpStream();

				
				cout << "output: " << endl;
				for (int i = 0; i < p.output.size(); i++)
				{
					cout << p.output[i] << " ";
				}
				cout << endl;
				p.errorNum_fun(target_AND_Gate);


				//���������
				/*
				out1 << p.weight[0][0][0] << "," << p.weight[0][1][0] << ", " << p.theta[0][1] << "\n";
				out_err << p.errorNum << "\n";
				*/
				if (p.errorNum == 0)
				{
					p.view();
					cout << "congraturation!" << endl;
					return 0;
				}
				n++;

			}
		}
		
		

		
		
		break;

	case 2:

		//OR_GATE
		p = Perceptron(2, 1, 2);
		p.random_initialize();
		p.UpStream();
		p.errorNum_fun(target_OR_Gate);
		p.view();

		//���������
		//out1 << p.weight[0][0][0] << "," << p.weight[0][1][0] << ", " << p.theta[0][1] << "\n";
		if (p.errorNum == 0)
		{
			p.view();
			cout << "congraturation!" << endl;
			return 0;
		}
		else
		{
			n = 0;
			while (1)
			{
				cout << n + 1 << "��° learning..." << endl;
				p.BackStream(n % 4, target_OR_Gate);
				p.learning(n % 4, target_OR_Gate);
				p.UpStream();

				//���������
				//out1 << p.weight[0][0][0] << "," << p.weight[0][1][0] << ", " << p.theta[0][1] << "\n";
				cout << "output: " << endl;
				for (int i = 0; i < p.output.size(); i++)
				{
					cout << p.output[i] << " ";
				}
				cout << endl;
				p.errorNum_fun(target_OR_Gate);
				//���������
				//out_err << p.errorNum << "\n";
				if (p.errorNum == 0)
				{
					p.view();
					cout << "congraturation!" << endl;
					return 0;
				}
				n++;

			}
		}
		break;

	case 3:

		//XOR_GATE
		p = Perceptron(2,2,2);
		p.random_initialize();
		p.UpStream();
		p.errorNum_fun(target_XOR_Gate);
		p.view();
		
		//���� �����
		/*
		out1 << p.weight[0][0][0] << "," << p.weight[0][1][0] << ", " << p.theta[0][1] << "\n" ;
		out2 << p.weight[0][0][1] << "," << p.weight[0][1][1] << ", " << p.theta[1][1] << "\n" ;
		out3 << p.weight[1][0][0] << "," << p.weight[1][1][0] << ", " << p.theta[0][2] << "\n" ;
		*/
		if (p.errorNum == 0)
		{
			p.view();
			cout << "congraturation!" << endl;
			return 0;
		}
		else
		{
			n = 0;
			while (1)
			{
				cout << n + 1 << "��° learning..."<<endl;
				p.BackStream(n % 4, target_XOR_Gate);
				p.learning(n % 4, target_XOR_Gate);
				p.UpStream();
				cout << "output: " << endl;
				for (int i = 0; i < p.output.size(); i++)
				{
					cout << p.output[i] << " ";
				}
				cout << endl;

				//���������
				/*
				out1 <<  p.weight[0][0][0] << "," << p.weight[0][1][0] << ", " << p.theta[0][1] << "\n" ;
				out2 <<  p.weight[0][0][1] << "," << p.weight[0][1][1] << ", " << p.theta[1][1] << "\n" ;
				out3 <<  p.weight[1][0][0] << "," << p.weight[1][1][0] << ", " << p.theta[0][2] << "\n" ;
				*/
				p.errorNum_fun(target_XOR_Gate);

				//���������
				//out_err << p.errorNum << "\n";
				if (p.errorNum == 0)
				{
					p.view();
					cout << "congraturation!" << endl;
					return 0;
				}
				n++;

			}
		}
		
				break;

	case 4:

		//dounut
		p = Perceptron(2,9,2,2);
		p.input = { {0,0} , {0,1},{1,0} , {1,1},{0.5,1},{1,0.5},{0,0.5},{0.5,0},{0.5,0.5} };
		
		p.random_initialize();
		p.UpStream();
		p.errorNum_fun(target_dounut_arr);
		p.view();

		//���������
		/*
		out1 << p.weight[0][0][0] << "," << p.weight[0][1][0] << ", " << p.theta[0][1] << "\n";
		out2 << p.weight[0][0][1] << "," << p.weight[0][1][1] << ", " << p.theta[1][1] << "\n";
		out3 << p.weight[1][0][0] << "," << p.weight[1][1][0] << ", " << p.theta[0][2] << "\n";
		*/

		if (p.errorNum == 0)
		{
			p.view();
			cout << "congraturation!" << endl;
			return 0;
		}
		else
		{
			n = 0;
			while (1)
			{
				cout << n + 1 << "��° learning..." << endl;
				p.BackStream(n % 9, target_dounut_arr);
				p.learning(n % 9, target_dounut_arr);
				p.UpStream();

				/*
				cout << "output: " << endl;
				
				for (int i = 0; i < p.output.size(); i++)
				{
					cout << p.output[i] << " ";
				}
				cout << endl;
				*/
				p.errorNum_fun(target_dounut_arr);

				//���������
				/*
				out1 << p.weight[0][0][0] << "," << p.weight[0][1][0] << ", " << p.theta[0][1] << "\n";
				out2 << p.weight[0][0][1] << "," << p.weight[0][1][1] << ", " << p.theta[1][1] << "\n";
				out3 << p.weight[1][0][0] << "," << p.weight[1][1][0] << ", " << p.theta[0][2] << "\n";
				*/
				//out_err << p.errorNum << "\n";
				if (p.errorNum == 0)
				{
					p.view();
					cout << "congraturation!" << endl;
					return 0;
				}
				n++;

			}
		}
		break;

	default:
		cout << "Input number is wrong , plz input number again.";
		cout << "If you want AND_GATE input number 1 " << endl;
		cout << "If you want OR_GATE input number 2 " << endl;
		cout << "If you want XOR_GATE input number 3 " << endl;
		cout << "Input number : ";
		cin >> tempNum;
		goto A;
	}
	
	
	
	
	
}
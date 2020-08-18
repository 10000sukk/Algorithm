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
	
	//모든 계산을 배열을 이용해서 하겠다..
	vector < vector<double>> input;
	vector< vector<vector<double>>> weight; // 3차원 weight 벡터 생성...[layer][out][in] 이런식으로 쓸것이다.
	vector< vector<vector<double>>> net;    // 3차원 net 벡터 생성 ....[input_row][node_row][node_col].... input의 경우의 수마다 해당하는 net들의 값을 다 저장하기 위한것
	vector< vector<double>> theta; //theta를 위한 2차원 벡터 생성..... [node_row][node_col]...... 각 노드의 f(net) 할때 필요한 theta를 위한 배열.... 
	vector< vector<vector<double>>> fnet; // net값이 theta보다 크거나 같으면 1 작으면 0  .....[input_row][node_row][node_col]
	vector< vector<vector<double>>> delta;     //delta를 저장하겟다.   [input_row][node_row][node_col]
	vector<int> colPerNodeNumber;  //column당 노드의 갯수를 적을 것이다
	vector<double> output;        // 마지막 노드에 해당하는 output 값을 입력 경우마다 저장 하겠다.
	vector<int> target_arr;       // target이 되는 값을 저장하는 배열을 만들겠다.
	



	int input_row;           //입력 경우의 수
	int input_col;           //입력의 갯수
	int layer;               // 몇층 짜리 인가
	int layerPerNodeNum;     //layer당 node의 갯수
	int node_row;            // 해당 노드의 row
	int node_col;            // node_col == layer + 1 
	int errorNum;
	double c = 3;
public:
	
	

	
	Perceptron()
	{

	}
	
	
	//n은 input node의 갯수
	//layer
	//layerPerNodeNum layer당 node의 갯수
	Perceptron(int n, int layer, int layerPerNodeNum)
	{
		this->input_row = (int)pow(2, n);
		this->input_col = n;
		this->layer = layer;
		this->layerPerNodeNum = layerPerNodeNum;

		//input 2차원 배열 생성
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


		//각 열마다 노드의 갯수를 저장하는 colPerNodeNumber를 입력하는 것
		colPerNodeNumber.resize(layer + 1 , 0);
		colPerNodeNumber[0] = input_col;
		colPerNodeNumber[layer] = 1;
		for (int i = 1; i < layer; i++)
		{
			colPerNodeNumber[i] = layerPerNodeNum;
			
			
		}

		
		//n 과 layerPerNodeNum중에 큰거 골라내기
		int max_n_layerPerNodeNum;

		if (n > layerPerNodeNum)
			max_n_layerPerNodeNum = n;
		else
			max_n_layerPerNodeNum = layerPerNodeNum;

		this->node_row = max_n_layerPerNodeNum;
		this->node_col = layer+1;
		


		//weight 3차원 vector 차근차근 밀어넣어서 공간 생성
		//단일 perceptron일 경우에 [1][input_col][1]
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



		//net 3차원 vector 차근차근 밀어넣어서 공간 생성
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

		//theta 2차원 배열 공간 확보
		for (int i = 0; i < max_n_layerPerNodeNum; i++)
		{
			vector<double> element;
			element.resize(layer+1);
			theta.push_back(element);
		}

		//fnet 3차원 배열 공간 확보
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

		//delta 3차원 배열 공간 생성
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

	//input이 0,1 외에도 있는 경우..
	Perceptron(int n, int n_row , int layer, int layerPerNodeNum)
	{
		this->input_row = n_row;
		this->input_col = n;
		this->layer = layer;
		this->layerPerNodeNum = layerPerNodeNum;

		

		//input 2차원 배열 생성
		for (int i = 0; i < input_row; i++)
		{
			vector<double> element;
			element.resize(input_col);
			input.push_back(element);
		}

		
		//각 열마다 노드의 갯수를 저장하는 colPerNodeNumber를 입력하는 것
		colPerNodeNumber.resize(layer + 1, 0);
		colPerNodeNumber[0] = input_col;
		colPerNodeNumber[layer] = 1;
		for (int i = 1; i < layer; i++)
		{
			colPerNodeNumber[i] = layerPerNodeNum;


		}


		//n 과 layerPerNodeNum중에 큰거 골라내기
		int max_n_layerPerNodeNum;

		if (n > layerPerNodeNum)
			max_n_layerPerNodeNum = n;
		else
			max_n_layerPerNodeNum = layerPerNodeNum;

		this->node_row = max_n_layerPerNodeNum;
		this->node_col = layer + 1;



		//weight 3차원 vector 차근차근 밀어넣어서 공간 생성
		//단일 perceptron일 경우에 [1][input_col][1]
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



		//net 3차원 vector 차근차근 밀어넣어서 공간 생성
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

		//theta 2차원 배열 공간 확보
		for (int i = 0; i < max_n_layerPerNodeNum; i++)
		{
			vector<double> element;
			element.resize(layer + 1);
			theta.push_back(element);
		}

		//fnet 3차원 배열 공간 확보
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

		//delta 3차원 배열 공간 생성
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
		//srand((unsigned int)time(NULL)); //씨드값 설정

		mt19937 random((random_device()()));
		uniform_real_distribution<double> dist(-1, 1);

		//weight 값 random 설정

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



		//theta 값 random 설정
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

		//input에서 net으로 갈때
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
		//layerPerNode에서 그 다음 net으로 갈때
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


	//w3 = -theta로 취급해서 시그모이드 돌리는 함수
	double F_sigmoid(double net )
	{
		
		return ( 1 / (1 + exp(-net))); // sigmoid
		
	}

	//activation function을 시그모이드로 하겠다
	//net 하고 난 다음에 활성함수에 넣어서 값을 저장하는 함수
	void fnet_fun(int input_row_Number, int node_column_Number)
	{
		for (int i = 0; i < colPerNodeNumber[node_column_Number]; i++)
		{

			fnet[input_row_Number][i][node_column_Number] = F_sigmoid(net[input_row_Number][i][node_column_Number]);
			
		}
	}
	

	//net 하고 f(net)을 한번에 해주는
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


	//Error 의 총합을 알려줌
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


	// 노드 열 단위로 delta를 뒤에서 부터 맞출수 있는 함수 
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
			// delta = f'(net) * (시그마 delta * weight)
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

	//layer Level 단위로 learning 과정 진행
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
						weight[i][j][k] +=  + (-c) * delta[input_row_Number][k][1] * input[input_row_Number][j];   // △weight = (-c) * delta * x ;

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
						weight[i][j][k] += (-c) * delta[input_row_Number][k][i+1] * fnet[input_row_Number][j][i];   // △weight = (-c) * delta * x ;

					}
				}

				for (int j = 0; j < colPerNodeNumber[i+1]; j++)
				{
					theta[j][i+1] += (-c) * delta[input_row_Number][j][i+1];
				}
			}

		}
		
	}


	//delta를 구하는 것을 한번에
	void BackStream(int input_row_Number,int* target_array)
	{
		for (int i = layer; i > 0; i--)
		{
			delta_fun(input_row_Number, i, target_array);
		}

		
	}


	//마지막에 학습에 성공하고 난 후에 배열들에 들어있는 값을 보여주기위한 것
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
		cout << "theta = w3라고 가정 " << endl;
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
			cout << "input_row : " << i << " 일 경우에" << endl;
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
			cout << "input_row : " << i << " 일 경우에" << endl;
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
			cout << " input_row : " << i << "에 대한 delta" << endl;
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

	//target 배열 생성
	int target_AND_Gate[4] = { 0,0,0,1 };
	int target_OR_Gate[4] = { 0,1,1,1 };
	int target_XOR_Gate[4] = { 0,1,1,0};
	int target_dounut_arr[9] = { 0,0,0,0,0,0,0,0,1 };
	int n;
	int tempNum; // 무슨 게이트의 학습을 원하는가를 입력 받을 것이다

	cout << "Which Gate do you want? select Gate" << endl;
	cout << "If you want AND_GATE input number 1 " << endl;
	cout << "If you want OR_GATE input number 2 " << endl;
	cout << "If you want XOR_GATE input number 3 " << endl;
	cout << "If you want dounut  input number4" << endl;
	cout << "Input number : ";
	cin >> tempNum;

	//시각화에 필요한 파일 입출력
	/*
	ofstream out1("C:\\Users\\김환석\\Desktop\\동고비\\test1.csv");
	ofstream out2("C:\\Users\\김환석\\Desktop\\동고비\\test2.csv");
	ofstream out3("C:\\Users\\김환석\\Desktop\\동고비\\test3.csv");
	ofstream out_err("C:\\Users\\김환석\\Desktop\\동고비\\error.csv");
	string buffer;
	*/

	//객체 생성
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

		//파일 입출력
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
				cout << n + 1 << "번째 learning..." << endl;
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


				//파일입출력
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

		//파일입출력
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
				cout << n + 1 << "번째 learning..." << endl;
				p.BackStream(n % 4, target_OR_Gate);
				p.learning(n % 4, target_OR_Gate);
				p.UpStream();

				//파일입출력
				//out1 << p.weight[0][0][0] << "," << p.weight[0][1][0] << ", " << p.theta[0][1] << "\n";
				cout << "output: " << endl;
				for (int i = 0; i < p.output.size(); i++)
				{
					cout << p.output[i] << " ";
				}
				cout << endl;
				p.errorNum_fun(target_OR_Gate);
				//파일입출력
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
		
		//파일 입출력
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
				cout << n + 1 << "번째 learning..."<<endl;
				p.BackStream(n % 4, target_XOR_Gate);
				p.learning(n % 4, target_XOR_Gate);
				p.UpStream();
				cout << "output: " << endl;
				for (int i = 0; i < p.output.size(); i++)
				{
					cout << p.output[i] << " ";
				}
				cout << endl;

				//파일입출력
				/*
				out1 <<  p.weight[0][0][0] << "," << p.weight[0][1][0] << ", " << p.theta[0][1] << "\n" ;
				out2 <<  p.weight[0][0][1] << "," << p.weight[0][1][1] << ", " << p.theta[1][1] << "\n" ;
				out3 <<  p.weight[1][0][0] << "," << p.weight[1][1][0] << ", " << p.theta[0][2] << "\n" ;
				*/
				p.errorNum_fun(target_XOR_Gate);

				//파일입출력
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

		//파일입출력
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
				cout << n + 1 << "번째 learning..." << endl;
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

				//파일입출력
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
template <typename T>
class Matrix {
//	private:
	public:
		T **matrix;

	public:
		int N_rows,
			 N_cols,
			 N;

		Matrix() {
			N_rows = 0;
			N_cols = 0;
			N = 0;
			matrix = NULL;
		}
		Matrix(int n_N_rows, int n_N_cols): N_rows(n_N_rows), N_cols(n_N_cols) {
			matrix = new T* [N_rows];

			for (int i = 0; i < N_rows; i++)
				matrix[i] = new T[N_cols];
		}//Matrix(int n_N_rows, int n_N_cols)

		~Matrix() {
			if (matrix) {
				for (int i = 0; i < N_rows; i++)
					delete [] matrix[i];
	
				delete [] matrix;
			}
		}//~Matrix

		void resize(int n_N_rows, int n_N_cols) {
			if (matrix) {
				for (int i = 0; i < N_rows; i++)
					delete [] matrix[i];
	
				delete [] matrix;
			}

			N_rows = n_N_rows;
			N_cols = n_N_cols;

			matrix = new T* [N_rows];

			for (int i = 0; i < N_rows; i++)
				matrix[i] = new T[N_cols];
		}//resize(int n_N_rows, int n_N_cols)

		T* operator[](int loc) {
			return matrix[loc];
		}//operator[](int loc)

};//Matrix class

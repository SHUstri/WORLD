#pragma once

namespace HexMapGenerator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	struct Vertex;
	struct Center;
	struct Polygon;
	struct Position;

	struct Position {
		int X;
		int Y;
	};

	struct Vertex {
		unsigned int id;
		unsigned char next_polygon_num;
		Polygon* polygons[3];
		Position position;
	};

	struct Polygon {
		unsigned int id;
		unsigned char next_vertex_num;
		Center* center;
		Vertex* vertexes[6];
		Polygon* neighbours[6];
	};

	struct Center {
		unsigned int id;
		Polygon* polygon;
		Position position;
	};

	/// <summary>
	/// Summary for Viewer
	/// </summary>
	public ref class Viewer : public System::Windows::Forms::Form
	{
	public:
		Viewer(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Viewer()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::TextBox^  RadiusBox;
	private: System::Windows::Forms::Button^  CreateDataBtn;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  ShowDataBtn;
	private: unsigned int num_of_polygons = 0;
	private: Polygon* polygons = 0;
	private: unsigned int num_of_centers = 0;
	private: Center* centers = 0;
	private: unsigned int num_of_vertexes = 0;
	private: Vertex* vertexes = 0;
	private: unsigned int radius = 0;
	private:
		void LinkPolygonAndVertex(unsigned int polygon_index, unsigned int vertex_index) {
			polygons[polygon_index].vertexes[polygons[polygon_index].next_vertex_num] = &(vertexes[vertex_index]);
			polygons[polygon_index].next_vertex_num++;

			vertexes[vertex_index].polygons[vertexes[vertex_index].next_polygon_num] = &(polygons[polygon_index]);
			vertexes[vertex_index].next_polygon_num++;
		}
	private:
		void LinkPolygonAndVertex(unsigned int polygon_index, unsigned int vertex_index, unsigned char position) {
			polygons[polygon_index].vertexes[position] = &(vertexes[vertex_index]);

			vertexes[vertex_index].polygons[vertexes[vertex_index].next_polygon_num] = &(polygons[polygon_index]);
			vertexes[vertex_index].next_polygon_num++;
		}
	private:
		void CopyVertexFromPolygon(unsigned int dst_polygon_index, unsigned int src_polygon_index, unsigned char src_vertex_index) {
			polygons[dst_polygon_index].vertexes[polygons[dst_polygon_index].next_vertex_num] = polygons[src_polygon_index].vertexes[src_vertex_index];
			polygons[dst_polygon_index].next_vertex_num++;

			polygons[src_polygon_index].vertexes[src_vertex_index]->polygons[polygons[src_polygon_index].vertexes[src_vertex_index]->next_polygon_num] = &(polygons[dst_polygon_index]);
			polygons[src_polygon_index].vertexes[src_vertex_index]->next_polygon_num++;
		}
	private:
		void CopyVertexFromPolygon(unsigned int dst_polygon_index, unsigned char dst_vertex_index, unsigned int src_polygon_index, unsigned char src_vertex_index) {
			polygons[dst_polygon_index].vertexes[dst_vertex_index] = polygons[src_polygon_index].vertexes[src_vertex_index];

			polygons[src_polygon_index].vertexes[src_vertex_index]->polygons[polygons[src_polygon_index].vertexes[src_vertex_index]->next_polygon_num] = &(polygons[dst_polygon_index]);
			polygons[src_polygon_index].vertexes[src_vertex_index]->next_polygon_num++;
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->RadiusBox = (gcnew System::Windows::Forms::TextBox());
			this->CreateDataBtn = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->ShowDataBtn = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(43, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Radius:";
			// 
			// RadiusBox
			// 
			this->RadiusBox->Location = System::Drawing::Point(62, 10);
			this->RadiusBox->Name = L"RadiusBox";
			this->RadiusBox->Size = System::Drawing::Size(100, 20);
			this->RadiusBox->TabIndex = 1;
			// 
			// CreateDataBtn
			// 
			this->CreateDataBtn->Location = System::Drawing::Point(16, 41);
			this->CreateDataBtn->Name = L"CreateDataBtn";
			this->CreateDataBtn->Size = System::Drawing::Size(75, 23);
			this->CreateDataBtn->TabIndex = 2;
			this->CreateDataBtn->Text = L"Create Data";
			this->CreateDataBtn->UseVisualStyleBackColor = true;
			this->CreateDataBtn->Click += gcnew System::EventHandler(this, &Viewer::CreateDataBtn_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(168, 10);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(600, 600);
			this->pictureBox1->TabIndex = 3;
			this->pictureBox1->TabStop = false;
			// 
			// ShowDataBtn
			// 
			this->ShowDataBtn->Location = System::Drawing::Point(16, 71);
			this->ShowDataBtn->Name = L"ShowDataBtn";
			this->ShowDataBtn->Size = System::Drawing::Size(75, 23);
			this->ShowDataBtn->TabIndex = 4;
			this->ShowDataBtn->Text = L"Show Data";
			this->ShowDataBtn->UseVisualStyleBackColor = true;
			this->ShowDataBtn->Click += gcnew System::EventHandler(this, &Viewer::ShowDataBtn_Click);
			// 
			// Viewer
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(779, 620);
			this->Controls->Add(this->ShowDataBtn);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->CreateDataBtn);
			this->Controls->Add(this->RadiusBox);
			this->Controls->Add(this->label1);
			this->Name = L"Viewer";
			this->Text = L"Viewer";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void CreateDataBtn_Click(System::Object^  sender, System::EventArgs^  e) {
				 radius = System::Convert::ToInt32(RadiusBox->Text);

				 num_of_polygons = 1 + 3*(radius + 1)*radius;
				 if (polygons != 0) {
					 delete polygons;
				 }
				 polygons = new Polygon[num_of_polygons];

				 num_of_centers = num_of_polygons;
				 if (centers != 0) {
					 delete centers;
				 }
				 centers = new Center[num_of_centers];

				 num_of_vertexes = 6 * (radius + 1)*(radius + 1);
				 if (vertexes != 0) {
					 delete vertexes;
				 }
				 vertexes = new Vertex[num_of_vertexes];

				 for (unsigned int c = 0; c < num_of_centers; ++c) {
					 centers[c].id = c;
					 centers[c].polygon = &polygons[c];
					 centers[c].position.X = 0;
					 centers[c].position.Y = 0;
				 }

				 unsigned int p;
				 for (p = 0; p < num_of_polygons; ++p) {
					 polygons[p].id = p;
					 polygons[p].center = &centers[p];
					 polygons[p].next_vertex_num = 0;
					 polygons[p].neighbours[0] = 0;
					 polygons[p].neighbours[1] = 0;
					 polygons[p].neighbours[2] = 0;
					 polygons[p].neighbours[3] = 0;
					 polygons[p].neighbours[4] = 0;
					 polygons[p].neighbours[5] = 0;
				 }

				 unsigned int v = 0;
				 for ( v = 0; v < num_of_vertexes; ++v ) {
					 vertexes[v].id = v;
					 vertexes[v].next_polygon_num = 0;
					 vertexes[v].position.X = 0;
					 vertexes[v].position.Y = 0;
				 }
/*
				 polygons[0].vertexes[0] = &(vertexes[0]);
				 polygons[0].vertexes[1] = &(vertexes[1]);
				 polygons[0].vertexes[2] = &(vertexes[2]);
				 polygons[0].vertexes[3] = &(vertexes[3]);
				 polygons[0].vertexes[4] = &(vertexes[4]);
				 polygons[0].vertexes[5] = &(vertexes[5]);

				 vertexes[0].polygons[vertexes[0].next_polygon_num] = &(polygons[0]);
				 vertexes[0].next_polygon_num++;
				 vertexes[1].polygons[vertexes[1].next_polygon_num] = &(polygons[0]);
				 vertexes[1].next_polygon_num++;
				 vertexes[2].polygons[vertexes[2].next_polygon_num] = &(polygons[0]);
				 vertexes[2].next_polygon_num++;
				 vertexes[3].polygons[vertexes[3].next_polygon_num] = &(polygons[0]);
				 vertexes[3].next_polygon_num++;
				 vertexes[4].polygons[vertexes[4].next_polygon_num] = &(polygons[0]);
				 vertexes[4].next_polygon_num++;
				 vertexes[5].polygons[vertexes[5].next_polygon_num] = &(polygons[0]);
				 vertexes[5].next_polygon_num++;
*/
				 LinkPolygonAndVertex(0, 0);
				 LinkPolygonAndVertex(0, 1);
				 LinkPolygonAndVertex(0, 2);
				 LinkPolygonAndVertex(0, 3);
				 LinkPolygonAndVertex(0, 4);
				 LinkPolygonAndVertex(0, 5);

				 unsigned int vertex_index = 6;
				 p = 1;
				 char tmp = 0;
				 unsigned char gen3 = 0;
				 unsigned int calculated_vertex_num = 0;
				 unsigned char nei = 0;
				 v = 0;

				 for (unsigned int r = 1; r <= radius; r++) {
					 tmp = -1;
					 nei = 0;
					 for (p; p <= (3 * r * (r + 1)); ++p) {
						 if ( (p - 1) % r == 0 ) {
							 ++tmp;
							 gen3 = 1;
							 if (vertex_index == (6 * r * r)) {
								 calculated_vertex_num = 6 * (r + 1) * (r + 1) - 1;
								 LinkPolygonAndVertex(p, calculated_vertex_num, 5);

								 polygons[p].neighbours[4] = &(polygons[3*(r + 1)*r]);
								 polygons[3*(r + 1)*r].neighbours[1] = &(polygons[p]);
							 }
							 else {
								 LinkPolygonAndVertex(p, vertex_index - 1, (nei - 1) % 6);

								 polygons[p].neighbours[(4 + nei) % 6] = &(polygons[p - 1]);
								 polygons[p - 1].neighbours[(1 + nei) % 6] = &(polygons[p]);
							 }

							 LinkPolygonAndVertex(p, vertex_index, (nei + 0) % 6);
							 ++vertex_index;

							 LinkPolygonAndVertex(p, vertex_index, (nei + 1) % 6);
							 ++vertex_index;

							 LinkPolygonAndVertex(p, vertex_index, (nei + 2) % 6);
							 ++vertex_index;

							 if (r == 1) {
								 LinkPolygonAndVertex(p, p % 6, (3 + nei) % 6);
								 LinkPolygonAndVertex(p, p - 1, (4 + nei) % 6);

								 polygons[p].neighbours[(3 + nei) % 6] = &(polygons[0]);
								 polygons[0].neighbours[nei % 6] = &(polygons[p]);
							 }
							 else {
								 calculated_vertex_num = (r - 2) * 3 * (r - 1) + 1 + tmp * (r - 1);
								 CopyVertexFromPolygon(p, (3 + nei) % 6, calculated_vertex_num, (nei + 1) % 6);
								 CopyVertexFromPolygon(p, (4 + nei) % 6, calculated_vertex_num, (nei + 0) % 6);

								 polygons[p].neighbours[(3 + nei) % 6] = &(polygons[calculated_vertex_num]);
								 polygons[calculated_vertex_num].neighbours[nei % 6] = &(polygons[p]);
							 }

							 ++nei;
						 }
						 else {
							 LinkPolygonAndVertex(p, vertex_index - 1, (nei - 1) % 6);

							 LinkPolygonAndVertex(p, vertex_index, nei % 6);
							 ++vertex_index;

							 LinkPolygonAndVertex(p, vertex_index, (nei + 1) % 6);
							 ++vertex_index;

							 calculated_vertex_num = (r - 2) * 3 * (r - 1) + 1 + tmp * (r - 1) + ((p - 1) % r);
							 if (calculated_vertex_num % (3 * r * (r - 1) + 1) == 0) {
								 CopyVertexFromPolygon(p, (nei + 2) % 6, calculated_vertex_num - 6 * (r - 1), 0);
								 CopyVertexFromPolygon(p, (nei + 3) % 6, calculated_vertex_num - 6 * (r - 1), 5);

								 polygons[p].neighbours[(2 + nei) % 6] = &(polygons[calculated_vertex_num - 6 * (r - 1)]);
								 polygons[calculated_vertex_num - 6 * (r - 1)].neighbours[(-1 + nei) % 6] = &(polygons[p]);
							 }
							 else {
								 CopyVertexFromPolygon(p, (nei + 2) % 6, calculated_vertex_num, (nei + 0) % 6 );
								 CopyVertexFromPolygon(p, (nei + 3) % 6, calculated_vertex_num, (nei - 1) % 6);

								 polygons[p].neighbours[(2 + nei) % 6] = &(polygons[calculated_vertex_num]);
								 polygons[calculated_vertex_num].neighbours[(-1 + nei) % 6] = &(polygons[p]);
							 }
							 /*
							 if (gen3 == 1) {
								 CopyVertexFromPolygon(p, (nei + 4) % 6, calculated_vertex_num - 1, 2);
								 gen3 = 0;
							 }
							 else {
								 CopyVertexFromPolygon(p, (nei + 4) % 6, calculated_vertex_num - 1, 1);
							 }
							 */
							 CopyVertexFromPolygon(p, (nei + 4) % 6, calculated_vertex_num - 1, nei % 6);

							 polygons[p].neighbours[(3 + nei) % 6] = &(polygons[calculated_vertex_num-1]);
							 polygons[calculated_vertex_num-1].neighbours[nei % 6] = &(polygons[p]);
							 
							 polygons[p].neighbours[(4 + nei) % 6] = &(polygons[p - 1]);
							 polygons[p-1].neighbours[(1 + nei) % 6] = &(polygons[p]);
						 }
					 }
				 }
	}

	private: System::Void ShowDataBtn_Click(System::Object^  sender, System::EventArgs^  e) {
		int hexagon_diameter = 600 / (1 + 2 * radius) / 0.8;
		int hexagon_radius = hexagon_diameter / 2;
		unsigned int p = 0;

		unsigned int calculated_radius = 0.866f * hexagon_radius;

		int pos_center_x = 300;
		int pos_center_y = 300;

		Pen^ blackPen = gcnew Pen(Color::Black, 1.0f);
		array<Point>^ curvePoints = gcnew array< Point >(6);
		Point centerPoint = Point(0, 0);

		unsigned int v = 0;
		for (v = 0; v < 6; ++v) {
			curvePoints[v] = Point(0, 0);
		}

		pictureBox1->CreateGraphics()->Clear(Color::White);

		for (p = 0; p < num_of_polygons; ++p) {
			if (polygons[p].neighbours[0] != 0 && polygons[p].neighbours[0]->center->position.X == 0 && polygons[p].neighbours[0]->center->position.Y == 0) {
				polygons[p].neighbours[0]->center->position.X = polygons[p].center->position.X - calculated_radius;
				polygons[p].neighbours[0]->center->position.Y = polygons[p].center->position.Y + 1.5f * hexagon_radius;
			}
			if (polygons[p].neighbours[1] != 0 && polygons[p].neighbours[1]->center->position.X == 0 && polygons[p].neighbours[1]->center->position.Y == 0) {
				polygons[p].neighbours[1]->center->position.X = polygons[p].center->position.X + calculated_radius;
				polygons[p].neighbours[1]->center->position.Y = polygons[p].center->position.Y + 1.5f * hexagon_radius;
			}
			if (polygons[p].neighbours[2] != 0 && polygons[p].neighbours[2]->center->position.X == 0 && polygons[p].neighbours[2]->center->position.Y == 0) {
				polygons[p].neighbours[2]->center->position.X = polygons[p].center->position.X + 2 * calculated_radius;
				polygons[p].neighbours[2]->center->position.Y = polygons[p].center->position.Y;
			}
			if (polygons[p].neighbours[3] != 0 && polygons[p].neighbours[3]->center->position.X == 0 && polygons[p].neighbours[3]->center->position.Y == 0) {
				polygons[p].neighbours[3]->center->position.X = polygons[p].center->position.X + calculated_radius;
				polygons[p].neighbours[3]->center->position.Y = polygons[p].center->position.Y - 1.5f * hexagon_radius;
			}
			if (polygons[p].neighbours[4] != 0 && polygons[p].neighbours[4]->center->position.X == 0 && polygons[p].neighbours[4]->center->position.Y == 0) {
				polygons[p].neighbours[4]->center->position.X = polygons[p].center->position.X - calculated_radius;
				polygons[p].neighbours[4]->center->position.Y = polygons[p].center->position.Y - 1.5f * hexagon_radius;
			}
			if (polygons[p].neighbours[5] != 0 && polygons[p].neighbours[5]->center->position.X == 0 && polygons[p].neighbours[5]->center->position.Y == 0) {
				polygons[p].neighbours[5]->center->position.X = polygons[p].center->position.X - 2 * calculated_radius;
				polygons[p].neighbours[5]->center->position.Y = polygons[p].center->position.Y;
			}

			if (polygons[p].vertexes[0]->position.X == 0 && polygons[p].vertexes[0]->position.Y == 0) {
				polygons[p].vertexes[0]->position.X = polygons[p].center->position.X - calculated_radius;
				polygons[p].vertexes[0]->position.Y = polygons[p].center->position.Y + 0.5f * hexagon_radius;
			}
			if (polygons[p].vertexes[1]->position.X == 0 && polygons[p].vertexes[1]->position.Y == 0) {
				polygons[p].vertexes[1]->position.X = polygons[p].center->position.X;
				polygons[p].vertexes[1]->position.Y = polygons[p].center->position.Y + hexagon_radius;
			}
			if (polygons[p].vertexes[2]->position.X == 0 && polygons[p].vertexes[2]->position.Y == 0) {
				polygons[p].vertexes[2]->position.X = polygons[p].center->position.X + calculated_radius;
				polygons[p].vertexes[2]->position.Y = polygons[p].vertexes[0]->position.Y;
			}
			if (polygons[p].vertexes[3]->position.X == 0 && polygons[p].vertexes[3]->position.Y == 0) {
				polygons[p].vertexes[3]->position.X = polygons[p].vertexes[2]->position.X;
				polygons[p].vertexes[3]->position.Y = polygons[p].center->position.Y - 0.5f * hexagon_radius;
			}
			if (polygons[p].vertexes[4]->position.X == 0 && polygons[p].vertexes[4]->position.Y == 0) {
				polygons[p].vertexes[4]->position.X = polygons[p].center->position.X;
				polygons[p].vertexes[4]->position.Y = polygons[p].center->position.Y - hexagon_radius;
			}
			if (polygons[p].vertexes[5]->position.X == 0 && polygons[p].vertexes[5]->position.Y == 0) {
				polygons[p].vertexes[5]->position.X = polygons[p].vertexes[0]->position.X;
				polygons[p].vertexes[5]->position.Y = polygons[p].vertexes[3]->position.Y;
			}

			for (v = 0; v < 6; ++v) {
				curvePoints[v].X = pos_center_x + polygons[p].vertexes[v]->position.X;
				curvePoints[v].Y = pos_center_y - polygons[p].vertexes[v]->position.Y;
			}

			centerPoint.X = pos_center_x + polygons[p].center->position.X;
			centerPoint.Y = pos_center_y - polygons[p].center->position.X;

			pictureBox1->CreateGraphics()->DrawPolygon(blackPen, curvePoints);
			//pictureBox1->CreateGraphics()->DrawLine(blackPen, centerPoint, centerPoint);
		}
	}
};
}

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

	struct Vertex
	{
		unsigned int id;
		unsigned char next_polygon_num;
		Polygon* polygons[3];
	};

	struct Polygon
	{
		unsigned int id;
		unsigned char next_vertex_num;
		Center* center;
		Vertex* vertexes[6];
	};

	struct Center
	{
		unsigned int id;
		Polygon* polygon;
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
	private: Polygon* polygons = 0;
	private: Center* centers = 0;
	private: Vertex* vertexes = 0;
	private: 
		void LinkPolygonAndVertex(unsigned int polygon_index, unsigned int vertex_index) {
			polygons[polygon_index].vertexes[polygons[polygon_index].next_vertex_num] = &(vertexes[vertex_index]);
			polygons[polygon_index].next_vertex_num++;
			vertexes[vertex_index].polygons[vertexes[vertex_index].next_polygon_num] = &(polygons[polygon_index]);
			vertexes[vertex_index].next_polygon_num++;
		}
	private:
		void CopyVertexFromPolygon(unsigned int dst_polygon_index, unsigned int src_polygon_index, unsigned char src_vertex_index) {
			polygons[dst_polygon_index].vertexes[polygons[dst_polygon_index].next_vertex_num] = polygons[src_polygon_index].vertexes[src_vertex_index];
			polygons[dst_polygon_index].next_vertex_num++;
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
			this->CreateDataBtn->Text = L"CreateData";
			this->CreateDataBtn->UseVisualStyleBackColor = true;
			this->CreateDataBtn->Click += gcnew System::EventHandler(this, &Viewer::CreateDataBtn_Click);
			// 
			// Viewer
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(175, 74);
			this->Controls->Add(this->CreateDataBtn);
			this->Controls->Add(this->RadiusBox);
			this->Controls->Add(this->label1);
			this->Name = L"Viewer";
			this->Text = L"Viewer";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void CreateDataBtn_Click(System::Object^  sender, System::EventArgs^  e) {
				 unsigned int radius;
				 radius = System::Convert::ToInt32(RadiusBox->Text);

				 unsigned int num_of_polygons = 1 + 3*(radius + 1)*radius;
				 if (polygons != 0) {
					 delete polygons;
				 }
				 polygons = new Polygon[num_of_polygons];

				 unsigned int num_of_centers = num_of_polygons;
				 if (centers != 0) {
					 delete centers;
				 }
				 centers = new Center[num_of_centers];

				 unsigned int num_of_vertexes = 6 * (radius + 1)*(radius + 1);
				 if (vertexes != 0) {
					 delete vertexes;
				 }
				 vertexes = new Vertex[num_of_vertexes];

				 for (unsigned int c = 0; c < num_of_centers; ++c) {
					 centers[c].id = c;
					 centers[c].polygon = &polygons[c];
				 }

				 unsigned int p;
				 for (p = 0; p < num_of_polygons; ++p) {
					 polygons[p].id = p;
					 polygons[p].center = &centers[p];
					 polygons[p].next_vertex_num = 0;
				 }

				 for (unsigned int v = 0; v < num_of_vertexes; ++v) {
					 vertexes[v].id = v;
					 vertexes[v].next_polygon_num = 0;
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
				 this->LinkPolygonAndVertex(0, 0);
				 this->LinkPolygonAndVertex(0, 1);
				 this->LinkPolygonAndVertex(0, 2);
				 this->LinkPolygonAndVertex(0, 3);
				 this->LinkPolygonAndVertex(0, 4);
				 this->LinkPolygonAndVertex(0, 5);

				 unsigned int vertex_index = 6;
				 p = 1;
				 char tmp = 0;
				 unsigned char gen3 = 0;
				 unsigned int calculated_vertex_num = 0;

				 for (unsigned int r = 1; r <= radius; r++) {
					 tmp = -1;
					 for (p; p <= (3 * r * (r + 1)); ++p) {
						 if ( (p - 1) % r == 0 ) {
							 ++tmp;
							 gen3 = 1;
							 if (vertex_index == (6 * r * r)) {
								 calculated_vertex_num = 6 * (r + 1) * (r + 1) - 1;
/*
								 polygons[p].vertexes[polygons[p].next_vertex_num] = &(vertexes[calculated_vertex_num]);
								 polygons[p].next_vertex_num++;
								 vertexes[calculated_vertex_num].polygons[vertexes[calculated_vertex_num].next_polygon_num] = &(polygons[p]);
								 vertexes[calculated_vertex_num].next_polygon_num++;
*/
								 this->LinkPolygonAndVertex(p, calculated_vertex_num);
							 }
							 else {
								 //polygons[p].vertexes[polygons[p].next_vertex_num] = &(vertexes[vertex_index - 1]);
								 //polygons[p].next_vertex_num++;
								 //vertexes[vertex_index - 1].polygons[vertexes[vertex_index - 1].next_polygon_num] = &(polygons[p]);
								 //vertexes[vertex_index - 1].next_polygon_num++;

								 this->LinkPolygonAndVertex(p, vertex_index - 1);
							 }

							 //polygons[p].vertexes[polygons[p].next_vertex_num] = &(vertexes[vertex_index]);
							 //polygons[p].next_vertex_num++;
							 //vertexes[vertex_index].polygons[vertexes[vertex_index].next_polygon_num] = &(polygons[p]);
							 //vertexes[vertex_index].next_polygon_num++;
							 this->LinkPolygonAndVertex(p, vertex_index);
							 ++vertex_index;

							 //polygons[p].vertexes[polygons[p].next_vertex_num] = &(vertexes[vertex_index]);
							 //polygons[p].next_vertex_num++;
							 //vertexes[vertex_index].polygons[vertexes[vertex_index].next_polygon_num] = &(polygons[p]);
							 //vertexes[vertex_index].next_polygon_num++;
							 this->LinkPolygonAndVertex(p, vertex_index);
							 ++vertex_index;

							 //polygons[p].vertexes[polygons[p].next_vertex_num] = &(vertexes[vertex_index]);
							 //polygons[p].next_vertex_num++;
							 //vertexes[vertex_index].polygons[vertexes[vertex_index].next_polygon_num] = &(polygons[p]);
							 //vertexes[vertex_index].next_polygon_num++;
							 this->LinkPolygonAndVertex(p, vertex_index);
							 ++vertex_index;

							 if (r == 1) {
								 //polygons[p].vertexes[polygons[p].next_vertex_num] = &(vertexes[p % 6]);
								 //polygons[p].next_vertex_num++;
								 //vertexes[p].polygons[vertexes[p].next_polygon_num] = &(polygons[p % 6]);
								 //vertexes[p].next_polygon_num++;
								 this->LinkPolygonAndVertex(p, p % 6);

								 //polygons[p].vertexes[polygons[p].next_vertex_num] = &(vertexes[p - 1]);
								 //polygons[p].next_vertex_num++;
								 //vertexes[p - 1].polygons[vertexes[p - 1].next_polygon_num] = &(polygons[p]);
								 //vertexes[p - 1].next_polygon_num++;
								 this->LinkPolygonAndVertex(p, p - 1);
							 }
							 else {
								 calculated_vertex_num = (r - 2) * 3 * (r - 1) + 1 + tmp * (r - 1);
								 //polygons[p].vertexes[polygons[p].next_vertex_num] = polygons[calculated_vertex_num].vertexes[2];
								 //polygons[p].next_vertex_num++;
								 this->CopyVertexFromPolygon(p, calculated_vertex_num, 2);

								 //polygons[p].vertexes[polygons[p].next_vertex_num] = polygons[calculated_vertex_num].vertexes[1];
								 //polygons[p].next_vertex_num++;
								 this->CopyVertexFromPolygon(p, calculated_vertex_num, 1);
							 }
						 }
						 else {
							 //polygons[p].vertexes[polygons[p].next_vertex_num] = &(vertexes[vertex_index - 1]);
							 //polygons[p].next_vertex_num++;
							 //vertexes[vertex_index - 1].polygons[vertexes[vertex_index - 1].next_polygon_num] = &(polygons[p]);
							 //vertexes[vertex_index - 1].next_polygon_num++;
							 this->LinkPolygonAndVertex(p, vertex_index - 1);

							 //polygons[p].vertexes[polygons[p].next_vertex_num] = &(vertexes[vertex_index]);
							 //polygons[p].next_vertex_num++;
							 //vertexes[vertex_index].polygons[vertexes[vertex_index].next_polygon_num] = &(polygons[p]);
							 //vertexes[vertex_index].next_polygon_num++;
							 this->LinkPolygonAndVertex(p, vertex_index);
							 ++vertex_index;

							 //polygons[p].vertexes[polygons[p].next_vertex_num] = &(vertexes[vertex_index]);
							 //polygons[p].next_vertex_num++;
							 //vertexes[vertex_index].polygons[vertexes[vertex_index].next_polygon_num] = &(polygons[p]);
							 //vertexes[vertex_index].next_polygon_num++;
							 this->LinkPolygonAndVertex(p, vertex_index);
							 ++vertex_index;

							 calculated_vertex_num = (r - 2) * 3 * (r - 1) + 1 + tmp * (r - 1) + ((p - 1) % r);
							 if (calculated_vertex_num % (3 * r * (r - 1) + 1) == 0) {
								 //polygons[p].vertexes[polygons[p].next_vertex_num] = polygons[calculated_vertex_num - 6 * (r - 1)].vertexes[1];
								 //polygons[p].next_vertex_num++;
								 this->CopyVertexFromPolygon(p, calculated_vertex_num - 6 * (r - 1), 1);
								 //polygons[p].vertexes[polygons[p].next_vertex_num] = polygons[calculated_vertex_num - 6 * (r - 1)].vertexes[0];
								 //polygons[p].next_vertex_num++;
								 this->CopyVertexFromPolygon(p, calculated_vertex_num - 6 * (r - 1), 0);
							 }
							 else {
								 //polygons[p].vertexes[polygons[p].next_vertex_num] = polygons[calculated_vertex_num].vertexes[1];
								 //polygons[p].next_vertex_num++;
								 this->CopyVertexFromPolygon(p, calculated_vertex_num, 1);
								 //polygons[p].vertexes[polygons[p].next_vertex_num] = polygons[calculated_vertex_num].vertexes[0];
								 //polygons[p].next_vertex_num++;
								 this->CopyVertexFromPolygon(p, calculated_vertex_num, 0);
							 }

							 if (gen3 == 1) {
								 //polygons[p].vertexes[polygons[p].next_vertex_num] = polygons[calculated_vertex_num - 1].vertexes[2];
								 //polygons[p].next_vertex_num++;
								 this->CopyVertexFromPolygon(p, calculated_vertex_num-1, 2);
								 gen3 = 0;
							 }
							 else {
								 //polygons[p].vertexes[polygons[p].next_vertex_num] = polygons[calculated_vertex_num - 1].vertexes[1];
								 //polygons[p].next_vertex_num++;
								 this->CopyVertexFromPolygon(p, calculated_vertex_num-1, 1);
							 }
							 
						 }
					 }
				 }
	}
	};
}

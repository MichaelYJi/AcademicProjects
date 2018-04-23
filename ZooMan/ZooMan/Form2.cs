using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ZooManager
{

    public partial class Form2 : Form
    {

        private SqlConnectionStringBuilder builder;
        private SqlDataAdapter dataAdapter = new SqlDataAdapter();
        private BindingSource bindingSource1 = new BindingSource();

        public Form2()
        {
            InitializeComponent();

            try
            {
                builder = new SqlConnectionStringBuilder();
                builder.DataSource = "zoomangroup.database.windows.net";
                builder.UserID = "ZooMan_Admin";
                builder.Password = "ParsonsWinter2018!";
                builder.InitialCatalog = "ZooManager";

            }
            catch (SqlException e)
            {
                MessageBox.Show(e.ToString());
            }

            dataGridView1.DataSource = bindingSource1;

        }

        public SqlConnectionStringBuilder connector()
        {
            SqlConnectionStringBuilder builder = new SqlConnectionStringBuilder();
            builder.DataSource = "zoomangroup.database.windows.net";
            builder.UserID = "ZooMan_Admin";
            builder.Password = "ParsonsWinter2018!";
            builder.InitialCatalog = "ZooManager";
            return builder;
        }

        internal void SetActiveHome(Form1 form1)
        {
            throw new NotImplementedException();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            dataGridView1.ClearSelection();
            using (SqlConnection connect = new SqlConnection(connector().ConnectionString))
            {
                connect.Open();
                String query = "Select * from ZOOKEEPER, HUb where zookeeper.hubID = hub.id order by hubID;";
                GetData(query);
                connect.Close();
            }
        }

        public void GetData(string selectCommand)
        {
            try
            {
                SqlConnection connection = new SqlConnection(builder.ConnectionString);
                dataAdapter = new SqlDataAdapter(selectCommand, connection);

                SqlCommandBuilder commandBuilder = new SqlCommandBuilder(dataAdapter);

                DataTable table = new DataTable();
                table.Locale = System.Globalization.CultureInfo.InvariantCulture;
                dataAdapter.Fill(table);
                bindingSource1.DataSource = table;
            }
            catch (SqlException e)
            {
                MessageBox.Show(e.ToString());
            }
        }
    }
}

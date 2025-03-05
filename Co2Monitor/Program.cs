

// программа для пк которая будет сохранять данные
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Data;
using System.Data.Common;
using System;
using System.Formats.Tar;


DataSet SensorDataSet1 = new DataSet("SensorDataSet");
DataSet SensorDataSet2 = new DataSet("SensorDataSet");
DataSet SensorDataSet3 = new DataSet("SensorDataSet");
DataSet SensorDataSet4 = new DataSet("SensorDataSet");

DataTable SensorTable1 = new DataTable("SensorTable1");
DataTable SensorTable2 = new DataTable("SensorTable2");
DataTable SensorTable3 = new DataTable("SensorTable3");
DataTable SensorTable4 = new DataTable("SensorTable4");

SensorDataSet1.Tables.Add(SensorTable1);
SensorDataSet2.Tables.Add(SensorTable2);
SensorDataSet3.Tables.Add(SensorTable3);
SensorDataSet4.Tables.Add(SensorTable4);




#region SensorTable1

DataColumn HourId1 = new DataColumn("Hourid", Type.GetType("System.UInt64"));
HourId1.Unique = true; // столбец будет иметь уникальное значение
HourId1.AllowDBNull = false; // не может принимать null

DataColumn TimeStampColumn1 = new DataColumn("TimeStamp", Type.GetType("System.UInt64"));

DataColumn ECo2Column1 = new DataColumn("ECo2", Type.GetType("System.UInt16"));
DataColumn TVOCColumn1 = new DataColumn("TVOC", Type.GetType("System.UInt16"));

DataColumn TempIndoorColumn1 = new DataColumn("TempIndoor", Type.GetType("System.Byte"));
DataColumn HumIndoorColumn1 = new DataColumn("HumIndoor", Type.GetType("System.Byte"));
DataColumn TempOutdoorColumn1 = new DataColumn("TempOutdoor", Type.GetType("System.Byte"));
DataColumn HumOutdoorColumn1 = new DataColumn("HumOutdoor", Type.GetType("System.Byte"));

DataColumn WindowOpenColumn1 = new DataColumn("WindowOpen", Type.GetType("System.Boolean"));
DataColumn DoorOpenColumn1 = new DataColumn("DoorOpen", Type.GetType("System.Boolean"));

SensorTable1.Columns.Add(HourId1);
SensorTable1.Columns.Add(TimeStampColumn1);
SensorTable1.Columns.Add(ECo2Column1);
SensorTable1.Columns.Add(TVOCColumn1);
SensorTable1.Columns.Add(TempIndoorColumn1);
SensorTable1.Columns.Add(HumIndoorColumn1);
SensorTable1.Columns.Add(TempOutdoorColumn1);
SensorTable1.Columns.Add(HumOutdoorColumn1);
SensorTable1.Columns.Add(WindowOpenColumn1);
SensorTable1.Columns.Add(DoorOpenColumn1);

#endregion

#region SensorTable2
DataColumn HourId2 = new DataColumn("Hourid", Type.GetType("System.UInt64"));
HourId2.Unique = true; // столбец будет иметь уникальное значение
HourId2.AllowDBNull = false; // не может принимать null

DataColumn TimeStampColumn2 = new DataColumn("TimeStamp", Type.GetType("System.UInt64"));

DataColumn ECo2Column2 = new DataColumn("ECo2", Type.GetType("System.UInt16"));
DataColumn TVOCColumn2 = new DataColumn("TVOC", Type.GetType("System.UInt16"));

DataColumn TempIndoorColumn2 = new DataColumn("TempIndoor", Type.GetType("System.Byte"));
DataColumn HumIndoorColumn2 = new DataColumn("HumIndoor", Type.GetType("System.Byte"));
DataColumn TempOutdoorColumn2 = new DataColumn("TempOutdoor", Type.GetType("System.Byte"));
DataColumn HumOutdoorColumn2 = new DataColumn("HumOutdoor", Type.GetType("System.Byte"));

DataColumn WindowOpenColumn2 = new DataColumn("WindowOpen", Type.GetType("System.Boolean"));
DataColumn DoorOpenColumn2 = new DataColumn("DoorOpen", Type.GetType("System.Boolean"));

SensorTable2.Columns.Add(HourId2);
SensorTable2.Columns.Add(TimeStampColumn2);
SensorTable2.Columns.Add(ECo2Column2);
SensorTable2.Columns.Add(TVOCColumn2);
SensorTable2.Columns.Add(TempIndoorColumn2);
SensorTable2.Columns.Add(HumIndoorColumn2);
SensorTable2.Columns.Add(TempOutdoorColumn2);
SensorTable2.Columns.Add(HumOutdoorColumn2);
SensorTable2.Columns.Add(WindowOpenColumn2);
SensorTable2.Columns.Add(DoorOpenColumn2);
#endregion

#region SensorTable3

DataColumn HourId3 = new DataColumn("Hourid", Type.GetType("System.UInt64"));
HourId3.Unique = true; // столбец будет иметь уникальное значение
HourId3.AllowDBNull = false; // не может принимать null

DataColumn TimeStampColumn3 = new DataColumn("TimeStamp", Type.GetType("System.UInt64"));

DataColumn ECo2Column3 = new DataColumn("ECo2", Type.GetType("System.UInt16"));
DataColumn TVOCColumn3 = new DataColumn("TVOC", Type.GetType("System.UInt16"));

DataColumn TempIndoorColumn3 = new DataColumn("TempIndoor", Type.GetType("System.Byte"));
DataColumn HumIndoorColumn3 = new DataColumn("HumIndoor", Type.GetType("System.Byte"));
DataColumn TempOutdoorColumn3 = new DataColumn("TempOutdoor", Type.GetType("System.Byte"));
DataColumn HumOutdoorColumn3 = new DataColumn("HumOutdoor", Type.GetType("System.Byte"));

DataColumn WindowOpenColumn3 = new DataColumn("WindowOpen", Type.GetType("System.Boolean"));
DataColumn DoorOpenColumn3 = new DataColumn("DoorOpen", Type.GetType("System.Boolean"));

SensorTable3.Columns.Add(HourId3);
SensorTable3.Columns.Add(TimeStampColumn3);
SensorTable3.Columns.Add(ECo2Column3);
SensorTable3.Columns.Add(TVOCColumn3);
SensorTable3.Columns.Add(TempIndoorColumn3);
SensorTable3.Columns.Add(HumIndoorColumn3);
SensorTable3.Columns.Add(TempOutdoorColumn3);
SensorTable3.Columns.Add(HumOutdoorColumn3);
SensorTable3.Columns.Add(WindowOpenColumn3);
SensorTable3.Columns.Add(DoorOpenColumn3);
#endregion

#region SensorTable4

DataColumn HourId4 = new DataColumn("Hourid", Type.GetType("System.UInt64"));
HourId4.Unique = true; // столбец будет иметь уникальное значение
HourId4.AllowDBNull = false; // не может принимать null

DataColumn TimeStampColumn4 = new DataColumn("TimeStamp", Type.GetType("System.UInt64"));

DataColumn ECo2Column4 = new DataColumn("ECo2", Type.GetType("System.UInt16"));
DataColumn TVOCColumn4 = new DataColumn("TVOC", Type.GetType("System.UInt16"));

DataColumn TempIndoorColumn4 = new DataColumn("TempIndoor", Type.GetType("System.Byte"));
DataColumn HumIndoorColumn4 = new DataColumn("HumIndoor", Type.GetType("System.Byte"));
DataColumn TempOutdoorColumn4 = new DataColumn("TempOutdoor", Type.GetType("System.Byte"));
DataColumn HumOutdoorColumn4 = new DataColumn("HumOutdoor", Type.GetType("System.Byte"));

DataColumn WindowOpenColumn4 = new DataColumn("WindowOpen", Type.GetType("System.Boolean"));
DataColumn DoorOpenColumn4 = new DataColumn("DoorOpen", Type.GetType("System.Boolean"));

SensorTable4.Columns.Add(HourId4);
SensorTable4.Columns.Add(TimeStampColumn4);
SensorTable4.Columns.Add(ECo2Column4);
SensorTable4.Columns.Add(TVOCColumn4);
SensorTable4.Columns.Add(TempIndoorColumn4);
SensorTable4.Columns.Add(HumIndoorColumn4);
SensorTable4.Columns.Add(TempOutdoorColumn4);
SensorTable4.Columns.Add(HumOutdoorColumn4);
SensorTable4.Columns.Add(WindowOpenColumn4);
SensorTable4.Columns.Add(DoorOpenColumn4);
#endregion

if (File.Exists("SensorTable1.xml"))
    SensorDataSet1.ReadXml("SensorTable1.xml");
if (File.Exists("SensorTable2.xml"))
    SensorDataSet2.ReadXml("SensorTable2.xml");
if (File.Exists("SensorTable3.xml"))
    SensorDataSet3.ReadXml("SensorTable3.xml");
if (File.Exists("SensorTable4.xml"))
    SensorDataSet4.ReadXml("SensorTable4.xml");

using var udpSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
Console.WriteLine("Hello, World!");

var localIP = new IPEndPoint(IPAddress.Parse("0.0.0.0"), 55530);
// начинаем прослушивание входящих сообщений
udpSocket.Bind(localIP);
Console.WriteLine("UDP-сервер запущен...");

byte[] data = new byte[256]; // буфер для получаемых данных
//адрес, с которого пришли данные
EndPoint remoteIp = new IPEndPoint(IPAddress.Any, 0);
// получаем данные в массив data
var result = await udpSocket.ReceiveFromAsync(data, remoteIp);
var message = Encoding.UTF8.GetString(data, 0, result.ReceivedBytes);

Console.WriteLine($"Получено {result.ReceivedBytes} байт");
Console.WriteLine($"Удаленный адрес: {result.RemoteEndPoint}");
Console.WriteLine(message);     // выводим полученное сообщение
if (message == "AreYouAlive\n")
{
    string messageto = "IAmOk\n";
    byte[] datato = Encoding.UTF8.GetBytes(messageto);
    //EndPoint remotePoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 5555);
    int bytes = await udpSocket.SendToAsync(datato, result.RemoteEndPoint);
    Console.WriteLine($"Отправлено {bytes} байт");
}
else
{
    byte[] EchoData = new byte[result.ReceivedBytes]; // буфер для получаемых данных
    EchoData = data;
    EchoData[5] = 15;
    int bytes = await udpSocket.SendToAsync(EchoData, result.RemoteEndPoint);
    Console.WriteLine($"Отправлено {bytes} байт");


    // Извлечение MAC-адреса (первые 6 байт)
    byte[] macAddressBytes = new byte[6];
    Array.Copy(data, 0, macAddressBytes, 0, 6);
    //string macAddress = BitConverter.ToString(macAddressBytes).Replace("-", ":");
    byte[] PcMac = new byte[6] { 0x04, 0x42, 0x1A, 0x30, 0x10, 0x07 };

    if (Enumerable.SequenceEqual(macAddressBytes, PcMac))
    {
        Console.WriteLine("My Mac");

        // Извлечение остальных данных
        ulong Timestamp = BitConverter.ToUInt64(data, 6);
        ulong timestampHour = BitConverter.ToUInt64(data, 14);
        uint ECo2 = BitConverter.ToUInt16(data, 22);
        uint TVOC = BitConverter.ToUInt16(data, 24);
        byte TempIndoor = data[26];
        byte HumIndoor = data[27];
        byte TempOutdoor = data[28];
        byte HumOutdoor = data[29];
        byte flags = data[30];
        byte sensorId = data[31];

        Console.WriteLine($"sensorId: {sensorId}");
        switch (sensorId)
        {
            case 1:
                for (int i = 0; i < SensorTable1.Rows.Count; i++)
                {
                    Console.WriteLine($"i: {i}");
                    DataRow r = SensorTable1.Rows[i];
                    if ((ulong)r.ItemArray[0] == timestampHour)
                    {
                        // Здесь вы можете использовать индекс i, чтобы узнать номер строки
                        Console.WriteLine($"Условие выполнено в строке: {i}");

                        SensorTable1.Rows[i]["ECo2"] = ECo2;
                        SensorTable1.Rows[i]["TVOC"] = TVOC;
                        SensorTable1.Rows[i]["TempIndoor"] = TempIndoor;
                        SensorTable1.Rows[i]["HumIndoor"] = HumIndoor;
                        SensorTable1.Rows[i]["TempOutdoor"] = TempOutdoor;
                        SensorTable1.Rows[i]["HumOutdoor"] = HumOutdoor;

                        SensorTable1.Rows[i]["WindowOpen"] = GetBit(flags, 0);
                        SensorTable1.Rows[i]["DoorOpen"] = GetBit(flags, 1);
                        goto EndSwitch;
 
                    }
                }
                SensorTable1.Rows.Add(new object[] { timestampHour, Timestamp, ECo2, TVOC, TempIndoor, HumIndoor, TempOutdoor, HumOutdoor, GetBit(flags, 0), GetBit(flags, 1) });
                break;
            case 2:
                for (int i = 0; i < SensorTable2.Rows.Count; i++)
                {
                    DataRow r = SensorTable2.Rows[i];
                    if ((ulong)r["Hourid"] == timestampHour)
                    {
                        // Здесь вы можете использовать индекс i, чтобы узнать номер строки
                        Console.WriteLine($"Условие выполнено в строке: {i}");

                        SensorTable2.Rows[i]["ECo2"] = ECo2;
                        SensorTable2.Rows[i]["TVOC"] = TVOC;
                        SensorTable2.Rows[i]["TempIndoor"] = TempIndoor;
                        SensorTable2.Rows[i]["HumIndoor"] = HumIndoor;
                        SensorTable2.Rows[i]["TempOutdoor"] = TempOutdoor;
                        SensorTable2.Rows[i]["HumOutdoor"] = HumOutdoor;

                        SensorTable2.Rows[i]["WindowOpen"] = GetBit(flags, 0);
                        SensorTable2.Rows[i]["DoorOpen"] = GetBit(flags, 1);
                        goto EndSwitch;

                    }
                }
                SensorTable2.Rows.Add(new object[] { timestampHour, Timestamp, ECo2, TVOC, TempIndoor, HumIndoor, TempOutdoor, HumOutdoor, GetBit(flags, 0), GetBit(flags, 1) });
                break;
            case 3:
                for (int i = 0; i < SensorTable3.Rows.Count; i++)
                {
                    DataRow r = SensorTable3.Rows[i];
                    if ((ulong)r["Hourid"] == timestampHour)
                    {
                        // Здесь вы можете использовать индекс i, чтобы узнать номер строки
                        Console.WriteLine($"Условие выполнено в строке: {i}");

                        SensorTable3.Rows[i]["ECo2"] = ECo2;
                        SensorTable3.Rows[i]["TVOC"] = TVOC;
                        SensorTable3.Rows[i]["TempIndoor"] = TempIndoor;
                        SensorTable3.Rows[i]["HumIndoor"] = HumIndoor;
                        SensorTable3.Rows[i]["TempOutdoor"] = TempOutdoor;
                        SensorTable3.Rows[i]["HumOutdoor"] = HumOutdoor;

                        SensorTable3.Rows[i]["WindowOpen"] = GetBit(flags, 0);
                        SensorTable3.Rows[i]["DoorOpen"] = GetBit(flags, 1);
                        goto EndSwitch;

                    }
                }
                SensorTable3.Rows.Add(new object[] { timestampHour, Timestamp, ECo2, TVOC, TempIndoor, HumIndoor, TempOutdoor, HumOutdoor, GetBit(flags, 0), GetBit(flags, 1) });
                break;
            case 4:
                for (int i = 0; i < SensorTable4.Rows.Count; i++)
                {
                    DataRow r = SensorTable4.Rows[i];
                    if ((ulong)r["Hourid"] == timestampHour)
                    {
                        // Здесь вы можете использовать индекс i, чтобы узнать номер строки
                        Console.WriteLine($"Условие выполнено в строке: {i}");

                        SensorTable4.Rows[i]["ECo2"] = ECo2;
                        SensorTable4.Rows[i]["TVOC"] = TVOC;
                        SensorTable4.Rows[i]["TempIndoor"] = TempIndoor;
                        SensorTable4.Rows[i]["HumIndoor"] = HumIndoor;
                        SensorTable4.Rows[i]["TempOutdoor"] = TempOutdoor;
                        SensorTable4.Rows[i]["HumOutdoor"] = HumOutdoor;

                        SensorTable4.Rows[i]["WindowOpen"] = GetBit(flags, 0);
                        SensorTable4.Rows[i]["DoorOpen"] = GetBit(flags, 1);
                        goto EndSwitch;

                    }
                }
                SensorTable4.Rows.Add(new object[] { timestampHour, Timestamp, ECo2, TVOC, TempIndoor, HumIndoor, TempOutdoor, HumOutdoor, GetBit(flags, 0), GetBit(flags, 1) });
                break;
            default:
                break;
        }
    EndSwitch:;

    }
    else
    {
        Console.WriteLine("Not My Mac");
    }




}
SensorDataSet1.WriteXml("SensorTable1.xml");
SensorDataSet2.WriteXml("SensorTable2.xml");
SensorDataSet3.WriteXml("SensorTable3.xml");
SensorDataSet4.WriteXml("SensorTable4.xml");

bool GetBit(byte b, int bitNumber)
{
    return (b & (1 << bitNumber)) != 0;
}

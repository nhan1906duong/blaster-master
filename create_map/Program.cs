using System;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;

namespace create_map
{
    class Program
    {
        static void Main(string[] args)
        {
            CreateFileMap();
        }

        public static void CreateFileMap()
        {
            using (StreamWriter sw = new StreamWriter(@$"E:\final\SE102\Blaster-Master\resources\overworld\scene2\map.txt"))
            {
                var source = new Bitmap(@"E:\final\SE102\Blaster-Master\resources\map\area2-overhead-map.png");
                for (int row = 30; row < 128; row++)
                {
                    for (int column = 0; column < 64; column++)
                    {
                        bool isFind = false;
                        Rectangle rect = new Rectangle(new Point(column * 16, row * 16), new Size(16, 16));
                        Bitmap bmp1 = CropImage(source, rect);
                        for (int tile = 0; tile < 143; tile++)
                        {
                            var bmp2 = new Bitmap(@$"E:\final\SE102\Blaster-Master\resources\map\overworld\{tile}.png");
                            if (SoSanh2AnhBitMap(bmp1, bmp2))
                            {
                                isFind = true;
                                sw.Write(tile + " ");
                                break;
                            }
                        }
                        if (!isFind)
                        {
                            sw.Write("Loi ");
                            Console.WriteLine($"Loi khong tim thay tile set tai row {row}, column {column}");
                        }
                    }
                    sw.WriteLine();
                }
            }
        }
        public static void moveFile()
        {
            String line;
            System.IO.StreamReader file =
            new System.IO.StreamReader(@"E:\final\SE102\Blaster-Master\resources\map\map-overworld.txt");
            int index = 0;
            while ((line = file.ReadLine()) != null)
            {
                System.Console.WriteLine(line);
                File.Move(@$"E:\final\SE102\Blaster-Master\resources\map\tile\{line}.png", @$"E:\final\SE102\Blaster-Master\resources\map\overworld\{index++}.png");
            }

            file.Close();
        }

        public static void TimTile()
        {
            int numTile = 1;
            var list = new ArrayList();
            list.Add(0);
            Console.WriteLine($"Item 1: 0");
            for (int index = 0; index < 128 * 128; index++)
            {
                if (index == 0)
                {
                    continue;
                }
                var bmp1 = new Bitmap(@"E:\final\SE102\Blaster-Master\resources\map\tile\" + index + ".png");
                bool isExist = false;
                for (int next = 0; next < list.Count; next++)
                {
                    var bmp2 = new Bitmap(@"E:\final\SE102\Blaster-Master\resources\map\tile\" + list[next] + ".png");
                    if (SoSanh2AnhBitMap(bmp1, bmp2))
                    {
                        isExist = true;
                        break;
                    }
                }
                if (!isExist)
                {
                    list.Add(index);
                    Console.WriteLine($"Item {++numTile}: {index}");
                }
            }
            using (StreamWriter sw = new StreamWriter(@$"E:\final\SE102\Blaster-Master\resources\map\map-overworld.txt"))
            {
                for (int num = 0; num < list.Count; num++)
                {
                    //
                    sw.WriteLine(list[num]);
                }
            }
            
        }
        public static void CatTileMapAreaWorld2()
        {
            var source = new Bitmap(@"E:\final\SE102\Blaster-Master\resources\map\area2-overhead-map.png");
            int index = 0;
            for (int row = 0; row < 128; row++)
            {
                for (int column = 0; column < 128; column++)
                {
                    Rectangle rect = new Rectangle(new Point(column * 16, row * 16), new Size(16, 16));

                    Bitmap bmp = CropImage(source, rect);
                    if (bmp == null)
                    {
                        Console.WriteLine("Loi cat anh" + index);
                    }
                    else
                    {
                        bmp.Save("E:/final/SE102/Blaster-Master/resources/map/tile/" + index + ".png", ImageFormat.Png);
                    }
                    ++index;
                }
            }
        }

        public static List<bool> GetHash(Bitmap bmpSource)
        {
            List<bool> lResult = new List<bool>();
            //create new image with 16x16 pixel
            Bitmap bmpMin = new Bitmap(bmpSource, new Size(16, 16));
            for (int j = 0; j < bmpMin.Height; j++)
            {
                for (int i = 0; i < bmpMin.Width; i++)
                {
                    //reduce colors to true / false                
                    lResult.Add(bmpMin.GetPixel(i, j).GetBrightness() < 0.5f);
                }
            }
            return lResult;
        }

        public static Bitmap CropImage(Bitmap source, Rectangle section)
        {
            // An empty bitmap which will hold the cropped image
            Bitmap bmp = new Bitmap(section.Width, section.Height);

            Graphics g = Graphics.FromImage(bmp);

            // Draw the given area (section) of the source image
            // at location 0,0 on the empty bitmap (bmp)
            g.DrawImage(source, 0, 0, section, GraphicsUnit.Pixel);

            return bmp;
        }

        public static bool SoSanh2AnhBitMap(Bitmap bmp1, Bitmap bmp2)
        {
            String img_1, img_2;
            if (bmp1.Width == bmp2.Width && bmp1.Height == bmp2.Height)
            {
                for (int i = 0; i < bmp1.Width; i++)
                    for (int j = 0; j < bmp1.Height; j++)
                    {
                        img_1 = bmp1.GetPixel(i, j).ToString();
                        img_2 = bmp2.GetPixel(i, j).ToString();
                        if (img_1 != img_2) return false;
                    }
                return true;
            }
            else return false;
        }
    }
}

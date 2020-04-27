import com.nsg.*;

import java.io.*;
import java.util.List;
import java.util.Random;

import com.alibaba.fastjson.JSON;

public class nsgtest {
    public void read_txt_data(String fname) {
        Nsg nsg = new Nsg(200, 200, 200, 10, 10, 100, 40, 50, 500);
        VecVecFloat vecVecFloat = new VecVecFloat();
        File file = new File(fname);
        try (BufferedReader bufferedReader = new BufferedReader(new FileReader(file))) {
            String line = null;
            while ((line = bufferedReader.readLine()) != null) {
                List<Float> v = JSON.parseArray(line, Float.class);
                VectorOfFloat vectorOfFloat = new VectorOfFloat();
                for (Float f : v) {
                    vectorOfFloat.add(f);
                }
                vecVecFloat.add(vectorOfFloat);
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        nsg.addAll(vecVecFloat);
        nsg.build();
    }

    public void load_binary_data(String fname) {
        Nsg nsg = new Nsg(200, 200, 200, 10, 10, 100, 40, 50, 500);
        nsg.load_data(fname);
        nsg.build();
    }

    public static void main(String[] args) {
        nsgtest test = new nsgtest();
//        test.read_txt_data("/tmp/txt_data");
//        test.load_binary_data("/run/media/tx/1ADC3E81DC3E56EB/TDDOWNLOAD/siftsmall/siftsmall_base.fvecs");
        test.load_binary_data("/run/media/tx/1ADC3E81DC3E56EB/TDDOWNLOAD/sift/sift_base.fvecs");
        if (1 / 1 == 1) {
            return;
        }
        //Nsg nsg = new Nsg("/run/media/tx/1ADC3E81DC3E56EB/TDDOWNLOAD/github/annbenmark/dataset/siftsmall/siftsmall_base.fvecs",
        //"/run/media/tx/1ADC3E81DC3E56EB/TDDOWNLOAD/github/annbenmark/dataset/siftsmall/siftsmall_query.fvecs",
        //"/run/media/tx/1ADC3E81DC3E56EB/TDDOWNLOAD/github/annbenmark/dataset/siftsmall/siftsmall_groundtruth.ivecs");
        Nsg nsg = new Nsg(200, 200, 200, 10, 10, 100, 40, 50, 500);
        VecVecFloat vecVecFloat = new VecVecFloat();
        Random random = new Random();
        for (int i = 0; i < 1000; ++i) {
            VectorOfFloat vectorOfFloat = new VectorOfFloat();
            for (int j = 0; j < 200; ++j) {
                vectorOfFloat.add(random.nextFloat());
            }
            vecVecFloat.add(vectorOfFloat);
        }
        nsg.addAll(vecVecFloat);
        nsg.build();
        VectorOfNeighbor vectorOfNeighbor = nsg.search(vecVecFloat.get(0), 200, 5);
        for (Neighbor neighbor : vectorOfNeighbor) {
            System.out.print(neighbor.getId() + " " + neighbor.getDistance());
            System.out.println();
        }
        System.out.println();
        nsg.save("/tmp/saved_data", "/tmp/saved_index");
        nsg.load("/tmp/saved_data", "/tmp/saved_index");
        vectorOfNeighbor = nsg.search(vecVecFloat.get(0), 200, 5);
        for (Neighbor neighbor : vectorOfNeighbor) {
            System.out.print(neighbor.getId() + " " + neighbor.getDistance());
            System.out.println();
        }
        System.out.println();
        nsg.optimizeGraph();
        vectorOfNeighbor = nsg.searchWithOptGraph(vecVecFloat.get(0), 200, 5);
        for (Neighbor neighbor : vectorOfNeighbor) {
            System.out.print(neighbor.getId() + " " + neighbor.getDistance());
            System.out.println();
        }
        System.out.println();
        nsg.close();

    }
}
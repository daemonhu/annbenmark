import com.nsg.test.*;

import java.util.Random;

public class nsgtest {

    public static void main(String[] args) {
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

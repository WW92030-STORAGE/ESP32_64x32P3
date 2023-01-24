import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class ImageToTHRESHOLD { // To be used with a 64x32 LED panel code
    static String toString(int x) {
        String s = Integer.toString(x, 16);
        while (s.length() < 2) s = "0" + s;
        return "0x" + s;
    }
    static String inputName = "INPUT.PNG"; // Input png file
    static String outputName = "output.txt"; // Output text file (contains formatted C++ code for a boolean array.)
    static int thresh = 80;

    public static void main(String[] args) throws IOException {
        BufferedImage bi = ImageIO.read(new File(inputName));
        // if (bi.getWidth() != 64) System.err.println("INVALID WIDTH");
        if (bi.getHeight() != 32) System.err.println("INVALID HEIGHT");

        FileWriter pw = new FileWriter(outputName); // Prints 3 java array codes
        Color[][] grid = new Color[bi.getWidth()][32];


        for (int i = 0; i < bi.getWidth(); i++) {
            for (int j = 0; j < 32; j++) {
                grid[i][j] = new Color(bi.getRGB(i, j));
            }
        }

        pw.write("bool grid[n][" + bi.getWidth() + "] = {");
        for (int i = 0; i < 32; i++) {
            if (i > 0) pw.write(", \n");
            pw.write("{");
            for (int j = 0; j < bi.getWidth(); j++) {
                if (j > 0) pw.write(", ");
                boolean nonzero = (grid[j][i].getRed() > thresh) || (grid[j][i].getGreen() > thresh) || (grid[j][i].getBlue() > thresh);
                pw.write(nonzero ? "1" : "0");
            }
            pw.write("}");
        }
        pw.write("};");

        pw.close();
    }
}

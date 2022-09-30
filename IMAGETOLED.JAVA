import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class ImageToLED { // To be used with a 64x32 LED panel code - Turns 64x32 pngs into arrays of RGB values.
    static String toString(int x) {
        String s = Integer.toString(x, 16);
        while (s.length() < 2) s = "0" + s;
        return "0x" + s;
    }
    static String inputName = "TEST.png"; // Input file image
    static String outputName = "output.txt"; // Output text file (contains formatted arrays of RGB components)
    public static void main(String[] args) throws IOException {
        BufferedImage bi = ImageIO.read(new File(inputName));
        if (bi.getWidth() != 64) System.err.println("INVALID WIDTH");
        if (bi.getHeight() != 32) System.err.println("INVALID HEIGHT");

        FileWriter pw = new FileWriter(outputName); // Prints 3 java array codes
        Color[][] grid = new Color[64][32];


        for (int i = 0; i < 64; i++) {
            for (int j = 0; j < 32; j++) {
                grid[i][j] = new Color(bi.getRGB(i, j));
            }
        }

        pw.write("uint8_t red[n][m] = {");
        for (int i = 0; i < 32; i++) {
            if (i > 0) pw.write(", \n");
            pw.write("{");
            for (int j = 0; j < 64; j++) {
                if (j > 0) pw.write(", ");
                pw.write(toString(grid[j][i].getRed()));
            }
            pw.write("}");
        }
        pw.write("};\n\n");

        pw.write("uint8_t green[n][m] = {");
        for (int i = 0; i < 32; i++) {
            if (i > 0) pw.write(", \n");
            pw.write("{");
            for (int j = 0; j < 64; j++) {
                if (j > 0) pw.write(", ");
                pw.write(toString(grid[j][i].getGreen()));
            }
            pw.write("}");
        }
        pw.write("};\n\n");

        pw.write("uint8_t blue[n][m] = {");
        for (int i = 0; i < 32; i++) {
            if (i > 0) pw.write(", \n");
            pw.write("{");
            for (int j = 0; j < 64; j++) {
                if (j > 0) pw.write(", ");
                pw.write(toString(grid[j][i].getBlue()));
            }
            pw.write("}");
        }
        pw.write("};\n\n");

        pw.close();
    }
}

import scala.io.Source

object WordCount {
  def main(args: Array[String]): Unit = {
    // read input from file
    val inputFileName = "input.txt"
    val input = readFile(inputFileName)

    val wordCount = countWords(input)
    println(s"Number of words: $wordCount")
  }

  def readFile(fileName: String): String = {
    val source = Source.fromFile(fileName)
    val content = try source.mkString finally source.close()
    content
  }

  def countWords(input: String): Int = {
    input.split("\\s+").length
  }
}

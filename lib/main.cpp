#include "transformers_tools.hpp"
#include <string>
int main(int argc, char *argv[]){
  // --- --- --- --- TRANSFORMERS objects
  TextTransformerWrap text_object = TextTransformerWrap();
  AudioTransformerWrap audio_object= AudioTransformerWrap();
  // --- --- --- --- Text Generation
  std::string generate_input = "你好,你";
  REQUESTS::memory generate_output = {
    .response=(char*)malloc(0),
    .size=0
  };
  text_object.generate_text(generate_input, &generate_output);
  fprintf(stdout,"TextTransformerWrap[generate_text]: %s\n",generate_output.response);
  free(generate_output.response);
  // --- --- --- --- Text translation
  // --- --- --- --- 
  std::string translate_input = "你好";
  REQUESTS::memory translate_output = {
    .response=(char*)malloc(0),
    .size=0
  };
  text_object.translate_zh_to_en(translate_input, &translate_output);
  fprintf(stdout,"TextTransformerWrap[translate_zh_to_en]: %s\n",translate_output.response);
  free(translate_output.response);
  // --- --- --- --- Speech to Text
  // --- --- --- --- ffmpeg -f alsa -ar 48000 -i hw:1 testfile.flac
  std::string transcript_input_file = "testfile.flac";
  REQUESTS::memory sinthetize_output = {
    .response=(char*)malloc(0),
    .size=0
  };
  audio_object.transcript_audio(transcript_input_file, &sinthetize_output);
  fprintf(stdout,"AudioTransformerWrap: %s\n",sinthetize_output.response);
  free(sinthetize_output.response);
  
}
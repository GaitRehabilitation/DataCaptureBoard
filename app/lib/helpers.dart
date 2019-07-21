import 'dart:convert';

import 'dart:math';

class helpers {

  static String numeric() => "0123456789";
  static String alphaLower() => "abcdefghijklmnopqrstuvwxyz";
  static String alphaUpper() => alphaLower().toUpperCase();

  static final Random _random = Random.secure();
  static String generateToken(int length, String tokens) {
    String result = '';
    for (int i = 0; i < length; i++) {
      result += tokens[_random.nextInt(tokens.length - 1)];
    }
    return result;
  }
}

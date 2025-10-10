#include "../include/rating.hpp"
#include "../include/review.hpp"  // Класс Review должен иметь метод getScore() или поле score

namespace classes {
Rating::Rating() : average(0.0), totalReviews(0), sumScores(0) {
}

void Rating::addReview(const std::shared_ptr<Review>& review) {
  if (!review)
    return;  // проверка на nullptr
  int score = review->GetScore();
  sumScores += score;
  totalReviews++;
  average = static_cast<double>(sumScores) / totalReviews;
}

double Rating::getAverage() const {
  return average;
}

int Rating::getTotalReviews() const {
  return totalReviews;
}

void Rating::reset() {
  average = 0.0;
  totalReviews = 0;
  sumScores = 0;
}
}  // namespace classes

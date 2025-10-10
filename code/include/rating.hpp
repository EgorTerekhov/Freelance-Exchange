#pragma once
#include <vector>
#include <memory>
namespace classes {
class Review;  // forward declaration

class Rating {
 private:
  double average;    // Средняя оценка
  int totalReviews;  // Количество отзывов
  int sumScores;     // Сумма всех оценок (для быстрого пересчета)

 public:
  Rating();

  // Добавляет новый отзыв и пересчитывает рейтинг
  void addReview(const std::shared_ptr<Review>& review);

  // Получить текущий рейтинг
  double getAverage() const;

  // Получить количество отзывов
  int getTotalReviews() const;

  // Сбросить рейтинг
  void reset();
};
}  // namespace classes